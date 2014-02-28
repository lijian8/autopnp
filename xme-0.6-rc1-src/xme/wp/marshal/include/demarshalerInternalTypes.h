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
 * $Id: demarshalerInternalTypes.h 4834 2013-08-28 09:36:55Z wiesmueller $
 */

/**
 * \file
 *
 * \brief  Internal data types for demarshaler waypoint. Only made visible so
 *         that the demarshaler code generated by XMT can access it.
 *         Do not use this otherwise.
 */

#ifndef XME_WP_MARSHAL_DEMARSHALERINTERNALTYPES_H
#define XME_WP_MARSHAL_DEMARSHALERINTERNALTYPES_H

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/hal/include/table.h"

#include "xme/core/topic.h"
#include "xme/core/dataManagerTypes.h"

/******************************************************************************/
/***   Type definitions                                                     ***/
/******************************************************************************/
XME_EXTERN_C_BEGIN

/**
 * \struct xme_wp_marshal_demarshaler_configurationItem_t
 *
 * \brief  Structure for storing waypoint configuration.
 */
typedef struct
{
    xme_core_topic_t topic; ///< Topic of the data that is stored at inputPort.
    xme_core_dataManager_dataPacketId_t inputPort; ///< InputPort where topic data is stored.
    xme_core_dataManager_dataPacketId_t outputPort; ///< OutputPort where marshaled data should be written to.
}
xme_wp_marshal_demarshaler_configurationItem_t;

/**
 * \brief  Type of table for storing this waypoint's configurations.
 */
typedef XME_HAL_TABLE
(
    xme_wp_marshal_demarshaler_configurationItem_t,
    xme_wp_marshal_demarshaler_configurationTable_t,
    XME_WP_MARSHAL_CONFIGURATIONTABLE_SIZE
);

/******************************************************************************/
/***   Global Variables                                                     ***/
/******************************************************************************/
/**
 * \brief  Table for storing this waypoint's configurations.
 */
extern xme_wp_marshal_demarshaler_configurationTable_t xme_wp_marshal_demarshaler_configurationTable;

XME_EXTERN_C_END

#endif //XME_WP_MARSHAL_DEMARSHALERINTERNALTYPES_H
