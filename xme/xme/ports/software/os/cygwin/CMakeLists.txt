#
# Copyright (c) 2011-2012, fortiss GmbH.
# Licensed under the Apache License, Version 2.0.
#
# Use, modification and distribution are subject to the terms specified
# in the accompanying license file LICENSE.txt located at the root directory
# of this software distribution. A copy is available at
# http://chromosome.fortiss.org/.
#
# This file is part of CHROMOSOME.
#
# $Id: CMakeLists.txt 3345 2013-05-17 12:07:58Z geisinger $
#
# File:
#         CMake configuration script for Cygwin platform port.
#

# Silence "CMake no longer defines WIN32 on Cygwin!" message
set (CMAKE_LEGACY_CYGWIN_WIN32 0 CACHE BOOL "Legacy warning about WIN32 not being defined on Cygwin platform")

xme_include_directory()
xme_add_subdirectory(xme)
