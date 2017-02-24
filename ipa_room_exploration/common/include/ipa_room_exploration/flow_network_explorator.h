// OpenCV
#include <opencv/cv.h>
#include <opencv/highgui.h>
// standard c++ includes
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <fstream>
#include <stdio.h>
// Eigen library for matrix/vector computations
#include <Eigen/Dense>
// Coin-Or library with Cbc mixed integer programming solver
#include <coin/OsiClpSolverInterface.hpp>
#include <coin/CoinModel.hpp>
#include <coin/CbcModel.hpp>
#include <coin/CbcHeuristicFPump.hpp>
// Coin-Or library with Clp linear programming solver
#include <coin/ClpSimplex.hpp>
// Boost libraries
#include <boost/config.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/adjacency_list.hpp>
// package specific includes
#include <ipa_room_exploration/fov_to_robot_mapper.h>
#include <ipa_room_exploration/A_star_pathplanner.h>
#include <ipa_room_exploration/distance_matrix.h>
#include <ipa_room_exploration/contains.h>
// msgs
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Polygon.h>
#include <geometry_msgs/Point32.h>

/*!
 *****************************************************************
 * \file
 *
 * \note
 * Copyright (c) 2016 \n
 * Fraunhofer Institute for Manufacturing Engineering
 * and Automation (IPA) \n\n
 *
 *****************************************************************
 *
 * \note
 * Project name: Care-O-bot
 * \note
 * ROS stack name: autopnp
 * \note
 * ROS package name: ipa_room_exploration
 *
 * \author
 * Author: Florian Jordan
 * \author
 * Supervised by: Richard Bormann
 *
 * \date Date of creation: 11.2016
 *
 * \brief
 *
 *
 *****************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer. \n
 * - Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution. \n
 * - Neither the name of the Fraunhofer Institute for Manufacturing
 * Engineering and Automation (IPA) nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission. \n
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License LGPL as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License LGPL for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License LGPL along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************/

// This struct is used to create arcs for the flow network, used to plan a coverage path trough the given map.
struct arcStruct
{
	cv::Point start_point;
	cv::Point end_point;
	double weight;
	std::vector<cv::Point> edge_points;
};

// typedef for boost, defining a directed graph
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS > directedGraph;

// TODO: update
// This class provides a coverage path planning algorithm based on a flow network. It spans such a network by going trough
// the given room map with a sweep line and defining edges of it whenever it touches an obstacle. From this touchpoint
// the edge is generated in a distance along the sweep line, that is equivalent to the given coverage radius, because the
// free space should determine the area that should be covered after this procedure. the sweep line goes first along the
// y-axis and then along the x-axis to create edges on every side of the obstacles. After this the arcs of the network
// are generated by taking the distance of two edges as its weight (gives two directed edges). To find a coverage path
// trough this flow network then a linear program is solved of the form
//		min 	c^T*w
//
// 		s.t. 	Vc >= 1 (elementwise)
//				sum(flows_into_node, r) - sum(flows_out_of_node, t+1) = 0; r=1:R-1
//				sum(flows, r) <= 1; r=0:R
//				sum(flows_out_of_start_node, 0) = 1
//				c(i+r*n)={0,1}
// where r determines different stages, i.e. steps in the coverage procedure, c(i+r*n)={0,1} determines whether an arc is
// gone at stage r, w storing the weights of the arcs, V storing if a cell of the discretized free space can be covered
// when using the arc corresponding to c(i), flows_into_node={0,1} determine if an arc into one edge is used,
// flows_out_of_node={0,1} determine if an arc out of the node is used and sum(flows, r) determine how many C(i+r*n) are
// equal to 1.
// The first constraint ensures that each cell of the free space is covered. The second constraint ensures that when an
// arc goes into an edge another arc out of this edge has be used to create a continous path. The third constraint ensures
// that only one edge is gone at every stage. The fourth constraint simply ensures to start at the node that one specifies.
// The parameter R, to determine how many stages there are, change during the process, until it is big enough for the
// optimization problem to find a feasible solution, because it can't be known at the start.
//
#pragma once

#define PI 3.14159265359

class flowNetworkExplorator
{
protected:
	// function that is used to create and solve a Cbc optimization problem out of the given matrices and vectors, using
	// the three-stage ansatz and single-flow cycle prevention constraints
	void solveThreeStageOptimizationProblem(std::vector<double>& C, const cv::Mat& V, const std::vector<double>& weights,
			const std::vector<std::vector<uint> >& flows_into_nodes, const std::vector<std::vector<uint> >& flows_out_of_nodes,
			const std::vector<uint>& start_arcs);

	// function that is used to create and solve a Cbc optimization problem out of the given matrices and vectors, using
	// the three-stage ansatz and lazy generalized cutset inequalities (GCI)
	void solveLazyConstraintOptimizationProblem(std::vector<double>& C, const cv::Mat& V, const std::vector<double>& weights,
			const std::vector<std::vector<uint> >& flows_into_nodes, const std::vector<std::vector<uint> >& flows_out_of_nodes,
			const std::vector<uint>& start_arcs);

	// function that checks if the given point is more close enough to any point in the given vector
	bool pointClose(const std::vector<cv::Point>& points, const cv::Point& point, const double min_distance);

	// object that plans a path from A to B using the Astar method
	AStarPlanner path_planner_;

public:
	// constructor
	flowNetworkExplorator();

	// Function that creates an exploration path for a given room. The room has to be drawn in a cv::Mat (filled with Bit-uchar),
	// with free space drawn white (255) and obstacles as black (0). It returns a series of 2D poses that show to which positions
	// the robot should drive at. The footprint stores a polygon that is used to determine the visibility at a specific
	// sensing pose. delta_theta provides an angular step to determine candidates for sensing poses.
	void getExplorationPath(const cv::Mat& room_map, std::vector<geometry_msgs::Pose2D>& path, const float map_resolution,
				const cv::Point starting_position, const cv::Point2d map_origin,
				const int cell_size, const geometry_msgs::Polygon& room_min_max_coordinates,
				const Eigen::Matrix<float, 2, 1>& robot_to_fov_middlepoint_vector, const float coverage_radius,
				const bool plan_for_footprint, const double path_eps, const double curvature_factor);

	// test function
	void testFunc();
};
