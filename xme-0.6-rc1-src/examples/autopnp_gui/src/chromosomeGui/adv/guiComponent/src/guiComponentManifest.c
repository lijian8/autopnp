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
 * $Id$
 */

/**
 * \file
 *         Defines function for creation of component type manifest
 *         for 'guiComponent'.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "chromosomeGui/adv/guiComponent/include/guiComponentManifest.h"

#include "chromosomeGui/topic/dictionary.h"
#include "chromosomeGui/topic/dictionaryData.h"

#include "xme/core/directory/include/attribute.h"
#include "xme/core/log.h"

#include "xme/hal/include/mem.h"
#include "xme/hal/include/safeString.h"
#include "xme/hal/include/time.h"

/******************************************************************************/
/***   Implementation                                                       ***/
/******************************************************************************/
xme_status_t
chromosomeGui_adv_guiComponent_manifest_createComponentTypeManifest
(
    xme_core_componentManifest_t* componentManifest
)
{
    uint32_t functionArrayLength;
    uint32_t portArrayLength;
    
    XME_CHECK
    (
        NULL != componentManifest,
        XME_STATUS_INVALID_PARAMETER
    );
    
    componentManifest->componentType = (xme_core_componentType_t)5001;

    functionArrayLength = sizeof(componentManifest->functionManifests) / sizeof(componentManifest->functionManifests[0]);

    // Function 'writeText'
    {
        if (0 >= functionArrayLength) // Check generated by tool (which does not know about the array size)
        {
            if (0 == functionArrayLength) // Only trigger warning once
            {
                XME_LOG
                (
                    XME_LOG_WARNING,
                    "%s:%d Component type 'guiComponent' defines more functions (%d) than can be stored in the manifest data structure (%d).\n",
                    __FILE__,
                    __LINE__,
                    2,
                    functionArrayLength
                );
            }
        }
        else
        {
            xme_core_functionManifest_t* functionManifest;
            
            functionManifest = &componentManifest->functionManifests[0];
            functionManifest->functionId = (xme_core_component_functionId_t)1;
            functionManifest->wcet = xme_hal_time_timeIntervalFromMilliseconds(200);
            functionManifest->alphaCurve.alphaCurve = 0;
            functionManifest->completion = true;
        }
    }
    
    
    // Function 'sendButtonState'
    {
        if (1 >= functionArrayLength) // Check generated by tool (which does not know about the array size)
        {
            if (1 == functionArrayLength) // Only trigger warning once
            {
                XME_LOG
                (
                    XME_LOG_WARNING,
                    "%s:%d Component type 'guiComponent' defines more functions (%d) than can be stored in the manifest data structure (%d).\n",
                    __FILE__,
                    __LINE__,
                    2,
                    functionArrayLength
                );
            }
        }
        else
        {
            xme_core_functionManifest_t* functionManifest;
            
            functionManifest = &componentManifest->functionManifests[1];
            functionManifest->functionId = (xme_core_component_functionId_t)2;
            functionManifest->wcet = xme_hal_time_timeIntervalFromMilliseconds(200);
            functionManifest->alphaCurve.alphaCurve = 0;
            functionManifest->completion = true;
        }
    }
    
    portArrayLength = sizeof(componentManifest->portManifests) / sizeof(componentManifest->portManifests[0]);

    // Subscription 'writeText'
    {
        if (0 >= portArrayLength) // Check generated by tool (which does not know about the array size)
        {
            if (0 == portArrayLength) // Only trigger warning once
            {
                XME_LOG
                (
                    XME_LOG_WARNING,
                    "%s:%d Component type 'guiComponent' defines more ports (%d) than can be stored in the manifest data structure (%d).\n",
                    __FILE__,
                    __LINE__,
                    2,
                    portArrayLength
                );
            }
        }
        else
        {
            xme_core_componentPortManifest_t* portManifest;
            
            portManifest = &componentManifest->portManifests[0];
            portManifest->portType = XME_CORE_COMPONENT_PORTTYPE_DCC_SUBSCRIPTION;
            portManifest->topic = CHROMOSOMEGUI_TOPIC_WRITETEXT; 
            portManifest->attrSet = XME_CORE_ATTRIBUTE_EMPTY_ATTRIBUTE_SET;
        }
    }
    
    
    // Publication 'buttonPushed'
    {
        if (1 >= portArrayLength) // Check generated by tool (which does not know about the array size)
        {
            if (1 == portArrayLength) // Only trigger warning once
            {
                XME_LOG
                (
                    XME_LOG_WARNING,
                    "%s:%d Component type 'guiComponent' defines more ports (%d) than can be stored in the manifest data structure (%d).\n",
                    __FILE__,
                    __LINE__,
                    2,
                    portArrayLength
                );
            }
        }
        else
        {
            xme_core_componentPortManifest_t* portManifest;
            
            portManifest = &componentManifest->portManifests[1];
            portManifest->portType = XME_CORE_COMPONENT_PORTTYPE_DCC_PUBLICATION;
            portManifest->topic = CHROMOSOMEGUI_TOPIC_BUTTONSIGNAL; 
            portManifest->attrSet = XME_CORE_ATTRIBUTE_EMPTY_ATTRIBUTE_SET;
            
        }
    }
    
    return XME_STATUS_SUCCESS;
}
