/*
 * Copyright (c) 2011-2013, fortiss GmbH.
 * Licensed under the Apache License, Version 2.0.
 *
 * Use, modification and distribution are subject to the terms specified
 * in the accompanying license file LICENSE.txt located at the root directory
 * of this software distribution. A copy is available at
 * http://chromosome.fortiss.org/.
 *
 * This file is part of CHROMOSOME.
 *
 * $Id: udpReceive.h 4765 2013-08-26 10:33:38Z gulati $
 */

/**
 * \file
 *
 * \brief  Waypoint that receieves the data from UDP network transportation.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (fortiss GmbH).
 */

#ifndef XME_WP_UDP_UDPRECEIVE_H
#define XME_WP_UDP_UDPRECEIVE_H

/**
 * \defgroup wp_udp UPD waypoint.
 * @{
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/core/component.h"
#include "xme/core/dataManagerTypes.h"

#include "xme/hal/include/net.h"

#include "xme/wp/waypoint.h"

#include <stdint.h>

/******************************************************************************/
/***   Prototypes                                                           ***/
/******************************************************************************/
XME_EXTERN_C_BEGIN

/**
 * \brief  Initialize this waypoint.
 *
 * \retval XME_STATUS_SUCCESS if the waypoint has been initialized successfully.
 * \retval XME_STATUS_INTERNAL_ERROR if an error occurred.
 */
xme_status_t
xme_wp_udp_udpReceive_init(void);

/**
 * \brief  Execute this waypoint.
 *
 * \details Before calling this, you must once add a configuration for the given
 *         instanceId, via xme_wp_udp_udpReceive_addConfig.
 *         Executing this function will receive the topic data from the Network
 *         of the associated configuration and output it on the dataId port. 
 *         The required network configuration is chosen from the input parameter
 *
 * \param  instanceId Id of the configuration for which to execute the waypoint, as returned by
 *         xme_wp_udpReceive_addConfig.
 *
 * \retval XME_STATUS_SUCCESS.
 * \retval XME_STATUS_INVALID_HANDLE if no configuration has been added for
 *         the given instanceId.
 * \retval XME_STATUS_INTERNAL_ERROR if there was an error reading from the
 *         network or writing to the output port. When this value is returned
 *         the output port value must be considered invalid.
 */
xme_status_t
xme_wp_udp_udpReceive_run
(
    xme_wp_waypoint_instanceId_t instanceId
);

/**
 * \brief  Check if the given configuration exists for this waypoint.
 *
 * \param  instanceId Pointer where id for the already existing config
 *         Only valid when XME_STATUS_SUCCESS has been returned.
 * \param  dataId     Pointer to data packet id which is used in the existsing config
 *         Only valid when XME_STATUS_SUCCESS has been returned.
 * \param  key        The key to correctly identify the intended receipent.
 * \param  port        port at which communication is to be opened for receiving.
 *
 * \retval XME_STATUS_SUCCESS if the configuration exists.
 * \retval XME_STATUS_NOT_FOUND if the configuration does not exists.
 */
xme_status_t
xme_wp_udp_udpReceive_getConfig
(
    xme_wp_waypoint_instanceId_t* instanceId,
    xme_core_dataManager_dataPacketId_t* dataId,
    void *key,
    uint16_t port
);

/**
 * \brief  Add a new configuration for this waypoint.
 *
 * \param  instanceId Pointer where id for the newly added configuration is written to.
 *         Only valid when XME_STATUS_SUCCESS has been returned.
 * \param  dataId    Output data port.
 * \param  sizeOfData    Size of the data which will appear at the data port.
 * \param  buffer    buffer space to be used to construct the network packets
 * \param  sizeOfBuffer    size of the buffer
 * \param  key        The key to correctly identify the intended receipent.
 * \param  port        port at which communication is to be opened for receiving.
 *
 * \retval XME_STATUS_SUCCESS if the configuration has been added successfully.
 * \retval XME_STATUS_OUT_OF_RESOURCES if the configuration could not be added due
 *         to resource constraints (e.g. not enough memory to store entry).
 */
xme_status_t
xme_wp_udp_udpReceive_addConfig
(
    xme_wp_waypoint_instanceId_t* instanceId,
    xme_core_dataManager_dataPacketId_t dataId,
    uint16_t sizeOfData,
    void *buffer,
    uint16_t sizeOfBuffer,
    void *key,
    uint16_t port
);

/**
 * \brief  Finalize this waypoint.
 *
 * \retval XME_STATUS_SUCCESS if the waypoint has been finalized successfully.
 * \retval XME_STATUS_INTERNAL_ERROR if an error occurred.
 */
xme_status_t
xme_wp_udp_udpReceive_fini(void);

/**
 * \brief  Calculates package over head required for header
 *
 * \return Number of bytes required to store the header.
 */
uint16_t
xme_wp_udp_udpReceive_getPackageOverHead(void);

XME_EXTERN_C_END

/**@}*/

#endif // #ifndef XME_WP_UDP_UDPRECEIVE_H
