/**
 * @file ARMAVLINK_Manager.c
 * @brief ARMavlink manager.
 * @date 11/13/2013
 * @author frederic.dhaeyer@parrot.com
 */
#include <stdlib.h>
#include <libARSAL/ARSAL_Print.h>
#include "ARMAVLINK_Manager.h"

/* ***************************************
 *
 *             define :
 *
 *****************************************/
#define ARMAVLINK_MANAGER_TAG    "ARMAVLINK_Manager"

ARMAVLINK_Manager_t* ARMAVLINK_Manager_New(eARMAVLINK_ERROR *error)
{
    ARMAVLINK_Manager_t *manager = NULL;
    eARMAVLINK_ERROR err = ARMAVLINK_OK;
    
    /* Check parameters */
    if(err == ARMAVLINK_OK)
    {
        /* Create the Manager */
        manager = malloc (sizeof (ARMAVLINK_Manager_t));
        if (manager == NULL)
        {
            err = ARMAVLINK_ERROR_ALLOC;
        }
    }
    
    if(err == ARMAVLINK_OK)
    {
        /* Initialize to default values */
        
    }

    /* delete the Manager if an error occurred */
    if (err != ARMAVLINK_OK)
    {
        ARSAL_PRINT (ARSAL_PRINT_ERROR, ARMAVLINK_MANAGER_TAG, "error: %s", ARMAVLINK_Error_ToString (err));
        ARMAVLINK_Manager_Delete (&manager);
    }
    
    /* return the error */
    if (error != NULL)
    {
        *error = err;
    }

    return manager;
}

void ARMAVLINK_Manager_Delete(ARMAVLINK_Manager_t **manager)
{
    ARMAVLINK_Manager_t *managerPtr = NULL;
    
    if (manager)
    {
        managerPtr = *manager;
        
        // Uninitialize here
        
        
        if (managerPtr)
        {
            free (managerPtr);
            managerPtr = NULL;
        }
        
        *manager = NULL;
    }
}
