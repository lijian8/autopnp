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
 *         Function wrapper - a generic abstraction for one executable function
 *              scheduled by the execution manager.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

#ifndef CHROMOSOMEGUI_ADV_COMPONENTONE_DOSOMETHINGFUNCTIONWRAPPER_H
#define CHROMOSOMEGUI_ADV_COMPONENTONE_DOSOMETHINGFUNCTIONWRAPPER_H

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/core/executionManager/include/executionManagerDataStructures.h"
#include "xme/core/log.h"

#include "xme/defines.h"

XME_EXTERN_C_BEGIN
/******************************************************************************/
/***   Prototypes                                                           ***/
/******************************************************************************/
/**
 * \brief  Start execution of function.
 *
 * \details This will start an infinite loop and execute the wrapped step
 *          function. Before each step call we wait until the execution
 *          managers signals that the function is ready to execute.
 *
 * \param  userFunctionDescRaw The xme_core_exec_functionDescriptor_t of the
 *         function that will be executed by this wrapper. Must not be null.
 *         If the given function descriptor has its pointer to the init
 *         function set, then this initialization function will be called
 *         once before the first call to the step function.
 */
void
chromosomeGui_adv_componentOne_doSomethingFunctionWrapper_execute
(
    void* userFunctionDescRaw
);

XME_EXTERN_C_END

#endif // #ifndef CHROMOSOMEGUI_ADV_COMPONENTONE_DOSOMETHINGFUNCTIONWRAPPER_H
