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
 * $Id: loginManagerProcessResponseFunction.c 4945 2013-09-04 07:37:46Z ruiz $
 */

/**
 * \file
 *         Source file for function loginManagerProcessResponse in component loginManager.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/core/login/include-gen/loginManagerProcessResponseFunction.h"

#include "xme/core/login/include-gen/loginManagerProcessResponseFunctionWrapper.h"
#include "xme/core/login/include-gen/loginManagerComponentWrapper.h"

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINMANAGERPROCESSRESPONSEFUNCTION_C_INCLUDES) ENABLED START
#include "xme/core/login/include/loginManager.h"
#include "xme/hal/include/net.h"
#include <inttypes.h>
// PROTECTED REGION END

/******************************************************************************/
/***   Static variables                                                     ***/
/******************************************************************************/
/**
 * \brief  Variable holding the value of the required output port 'outLoginResponse'.
 *
 * \details If necessary initialize this in the init function.
 *          The value of this variable will be written to the port at the end of
 *          the step function.
 */
static xme_core_topic_login_loginResponse_t
portOutLoginResponseData;

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINMANAGERPROCESSRESPONSEFUNCTION_C_STATICVARIABLES) ENABLED START
    
// PROTECTED REGION END

/******************************************************************************/
/***   Implementation                                                       ***/
/******************************************************************************/
xme_status_t
xme_core_login_loginManagerProcessResponseFunction_init
(
    void* param
)
{
    // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINMANAGERPROCESSRESPONSEFUNCTION_INITIALIZE_C) ENABLED START
    
    XME_UNUSED_PARAMETER(param);

    // Do nothing
    
    return XME_STATUS_SUCCESS;
    
    // PROTECTED REGION END
}

void
xme_core_login_loginManagerProcessResponseFunction_step
(
    void* param
)
{
    xme_status_t status[1];
    
    xme_core_topic_login_pnpLoginResponse_t portInPnPLoginResponseData; // Required port.
    xme_core_topic_login_loginResponse_t* portOutLoginResponseDataPtr = &portOutLoginResponseData;
    
    status[0] = xme_core_login_loginManagerComponentWrapper_readPortInPnPLoginResponse(&portInPnPLoginResponseData);
    
    {
        // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINMANAGERPROCESSRESPONSEFUNCTION_STEP_C) ENABLED START
        xme_com_interface_address_t interfaceAddress;
        char strIPAddress[XME_COM_INTERFACE_IPV4_STRING_BUFFER_SIZE];

        XME_UNUSED_PARAMETER(param);
        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == status[0], 
            XME_CHECK_RVAL_VOID, 
            XME_LOG_WARNING, 
            "The input parameter cannot be get."
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_ipv4ToGenericAddress
            (
                portInPnPLoginResponseData.ipAddress, 
                portInPnPLoginResponseData.ipAddress >> 8, 
                portInPnPLoginResponseData.ipAddress >> 16, 
                portInPnPLoginResponseData.ipAddress >> 24, 
                xme_hal_net_ntohs(portInPnPLoginResponseData.portAddress),
                &interfaceAddress
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "Cannot get the interface address from the login request.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_genericAddressToIPv4String
            (
                &interfaceAddress, strIPAddress, XME_COM_INTERFACE_IPV4_STRING_BUFFER_SIZE
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "Cannot transform ip address to string.\n"
        );

        XME_LOG
        (
            XME_LOG_NOTE, 
            "[LoginManager] Received a PnP Login Response for node %" PRIu16 " and IP address %s \n", 
            portInPnPLoginResponseData.nodeId,
            strIPAddress
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_core_login_loginManager_loginResponse(&portInPnPLoginResponseData, portOutLoginResponseDataPtr),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "The return value for login response was unsuccess"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_ipv4ToGenericAddress
            (
                portOutLoginResponseDataPtr->ipAddress, 
                portOutLoginResponseDataPtr->ipAddress >> 8, 
                portOutLoginResponseDataPtr->ipAddress >> 16, 
                portOutLoginResponseDataPtr->ipAddress >> 24, 
                xme_hal_net_ntohs(portOutLoginResponseDataPtr->portAddress),
                &interfaceAddress
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "Cannot get the interface address from the login request.\n"
        );

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == xme_com_interface_genericAddressToIPv4String
            (
                &interfaceAddress, strIPAddress, XME_COM_INTERFACE_IPV4_STRING_BUFFER_SIZE
            ),
            XME_CHECK_RVAL_VOID,
            XME_LOG_ERROR,
            "Cannot transform ip address to string.\n"
        );

        XME_LOG
        (
            XME_LOG_NOTE, 
            "[LoginManager] Sending a Login Response to node %d, identified by guid=%" PRIu64". PnPManager listening address is: %s. Status: %d \n", 
            portOutLoginResponseDataPtr->nodeId,
            portOutLoginResponseDataPtr->guid,
            strIPAddress,
            portOutLoginResponseDataPtr->loginStatus
        );
        
        // PROTECTED REGION END
    }
    
    status[0] = xme_core_login_loginManagerComponentWrapper_writePortOutLoginResponse(portOutLoginResponseDataPtr);
    
    {
        // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINMANAGERPROCESSRESPONSEFUNCTION_STEP_2_C) ENABLED START
    
        // TODO: Auto-generated stub
        //       Check return values of writePort calls here
        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == status[0], 
            XME_CHECK_RVAL_VOID, 
            XME_LOG_WARNING, 
            "The write port operation failed."
        );    
    
        // PROTECTED REGION END
    }
}

void
xme_core_login_loginManagerProcessResponseFunction_fini(void)
{
    // PROTECTED REGION ID(XME_CORE_LOGIN_LOGINMANAGERPROCESSRESPONSEFUNCTION_TERMINATE_C) ENABLED START
    
    // Do nothing
    
    // PROTECTED REGION END
}

// PROTECTED REGION ID(XME_CORE_LOGIN_LOGINMANAGERPROCESSRESPONSEFUNCTION_IMPLEMENTATION_C) ENABLED START

// PROTECTED REGION END
