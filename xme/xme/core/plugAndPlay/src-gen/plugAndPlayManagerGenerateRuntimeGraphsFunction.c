/*
 * Copyright (c) 2011-2014, fortiss GmbH.
 * Licensed under the Apache License, Version 2.0.
 *
 * Use, modification and distribution are subject to the terms specified
 * in the accompanying license file LICENSE.txt located at the root directory
 * of this software distribution. A copy is available at
 * http://chromosome.fortiss.org/.
 *
 * This file is part of CHROMOSOME.
 *
 * $Id: plugAndPlayManagerGenerateRuntimeGraphsFunction.c 7837 2014-03-14 12:33:13Z wiesmueller $
 */

/**
 * \file
 *         Source file for function pnpManagerGenerateRuntimeGraphs in component pnpManager.
 *
 * \author
 *         This file has been generated by the CHROMOSOME Modeling Tool (XMT)
 *         (fortiss GmbH).
 */

/******************************************************************************/
/***   Includes                                                             ***/
/******************************************************************************/
#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerGenerateRuntimeGraphsFunction.h"

#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerGenerateRuntimeGraphsFunctionWrapper.h"
#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerComponent.h"
#include "xme/core/plugAndPlay/include-gen/plugAndPlayManagerComponentWrapper.h"
#include "xme/core/plugAndPlay/include-gen/pnpManagerManifest.h"

#include "xme/core/logUtils.h"

#include "xme/hal/include/mem.h"

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_C_INCLUDES) ENABLED START
#include "xme/core/manifestRepository/include/manifestRepository.h"
#include "xme/core/plugAndPlay/include/plugAndPlayManager.h"
// PROTECTED REGION END

/******************************************************************************/
/***   Definitions                                                          ***/
/******************************************************************************/

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_C_DEFINITIONS) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Variables                                                            ***/
/******************************************************************************/
/**
 * \brief  Variable holding the value of the required output port 'outRuntimeGraph'.
 *
 * \details If necessary initialize this in the init function.
 *          The value of this variable will be written to the port at the end of
 *          the step function.
 */
static xme_core_topic_pnpManager_runtime_graph_model_t
portOutRuntimeGraphData;

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_C_VARIABLES) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Prototypes                                                           ***/
/******************************************************************************/

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_C_PROTOTYPES) ENABLED START

// PROTECTED REGION END

/******************************************************************************/
/***   Implementation                                                       ***/
/******************************************************************************/
xme_status_t
xme_core_pnp_pnpManagerGenerateRuntimeGraphsFunction_init
(
    xme_core_pnp_pnpManagerComponent_config_t* const componentConfig
)
{
    // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_INITIALIZE_C) ENABLED START

    // Nothing to do

    XME_UNUSED_PARAMETER(componentConfig);

    return XME_STATUS_SUCCESS;

    // PROTECTED REGION END
}

void
xme_core_pnp_pnpManagerGenerateRuntimeGraphsFunction_step
(
    xme_core_pnp_pnpManagerComponent_config_t* const componentConfig
)
{
    xme_status_t status[1];
    
    xme_core_topic_pnp_componentInstanceManifest_t portInComponentInstanceManifestData; // Optional port.
    xme_core_topic_pnpManager_runtime_graph_model_t* portOutRuntimeGraphDataPtr = &portOutRuntimeGraphData;
    
    (void)xme_hal_mem_set(&portInComponentInstanceManifestData, 0u, sizeof(xme_core_topic_pnp_componentInstanceManifest_t));
    
    status[0] = xme_core_pnp_pnpManagerComponentWrapper_readPortInComponentInstanceManifest(&portInComponentInstanceManifestData);
    
    {
        // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_STEP_C) ENABLED START

        XME_UNUSED_PARAMETER(componentConfig);

        portOutRuntimeGraphDataPtr = NULL;

        {
            xme_status_t returnValue;

            if (status[0] == XME_STATUS_SUCCESS)
            {
                XME_LOG
                (
                    XME_LOG_NOTE,
                    "[PnPManager] Received a Component Instance Manifest from node %d\n",
                    portInComponentInstanceManifestData.nodeId
                );

                XME_CHECK_MSG
                (
                    XME_STATUS_SUCCESS == xme_core_pnp_pnpManager_announceComponentInstanceManifest(&portInComponentInstanceManifestData),
                    XME_CHECK_RVAL_VOID,
                    XME_LOG_ERROR,
                    "[PnPManager] Cannot announce input component instance manifest for node %d.\n",
                    portInComponentInstanceManifestData.nodeId
                );
            }

            if (xme_core_pnp_pnpManager_hasNewRuntimeGraphs())
            {
                portOutRuntimeGraphDataPtr = &portOutRuntimeGraphData;
                returnValue = xme_core_pnp_pnpManager_getNextRuntimeGraph(portOutRuntimeGraphDataPtr);
                if (XME_STATUS_SUCCESS != returnValue)
                {
                    portOutRuntimeGraphDataPtr = NULL;
                }
                else
                {
                    XME_LOG
                    (
                        XME_LOG_NOTE, 
                        "[PnPManager] Sending a runtime graph to node %d.\n", 
                        portOutRuntimeGraphDataPtr->nodeId
                    );

                    // TODO: Setting all logical routes as established now.
                    // Ideally should be delayed till we receive an ACK (which is not sent yet).
                    // (Issue #3872)
                    XME_CHECK_MSG
                    (
                        XME_STATUS_SUCCESS == xme_core_pnp_pnpManager_setAllLogicalRoutesAsEstablished(),
                        XME_CHECK_RVAL_VOID,
                        XME_LOG_ERROR,
                        "[PnPManager] Cannot set logical routes as established.\n"
                    );
                }
            }
        }

        // PROTECTED REGION END
    }
    
    status[0] = xme_core_pnp_pnpManagerComponentWrapper_writePortOutRuntimeGraph(portOutRuntimeGraphDataPtr);
    
    {
        // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_STEP_2_C) ENABLED START

        XME_CHECK_MSG
        (
            XME_STATUS_SUCCESS == status[0] ||
            XME_STATUS_INVALID_PARAMETER == status[0], // This parameter is when we are not producing data.
            XME_CHECK_RVAL_VOID,
            XME_LOG_WARNING,
            "The write port operation failed."
        );

        // PROTECTED REGION END
    }
}

void
xme_core_pnp_pnpManagerGenerateRuntimeGraphsFunction_fini
(
    xme_core_pnp_pnpManagerComponent_config_t* const componentConfig
)
{
    // PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_TERMINATE_C) ENABLED START

    // Nothing to do

    XME_UNUSED_PARAMETER(componentConfig);

    // PROTECTED REGION END
}

// PROTECTED REGION ID(XME_CORE_PNP_PNPMANAGERGENERATERUNTIMEGRAPHSFUNCTION_IMPLEMENTATION_C) ENABLED START

// PROTECTED REGION END
