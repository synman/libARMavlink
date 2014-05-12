/**
 * @file autoTest.c
 * @brief libARMavlink TestBench automatic
 * @date 11/13/2013
 * @author frederic.dhaeyer@parrot.com
 */

/*****************************************
 *
 *             include file :
 *
 *****************************************/
#include <stdio.h>
#include <stdlib.h>

#include <libARSAL/ARSAL_Print.h>
#include <libARSAL/ARSAL_Thread.h>

#include <string.h>

#include <libARMavlink/libARMavlink.h>

/*****************************************
 *
 *             define :
 *
 *****************************************/

#define AUTOTEST_TAG "Autotest"


/*****************************************
 *
 *           declarations :
 *
 *****************************************/

/*****************************************
 *
 *          implementation :
 *
 *****************************************/

int main(int argc, char *argv[])
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    ARMAVLINK_Manager_t *managerPtr = ARMAVLINK_Manager_New(&error);
    if(error == ARMAVLINK_OK)
    {
        
        
        ARMAVLINK_Manager_Delete(&managerPtr);
    }
    else
    {
        // if there was an error in creating a new manager
        ARMAVLINK_Manager_Delete(&managerPtr);
    }
    
    fprintf(stderr, "%s\n", ARMAVLINK_Error_ToString(error));
    
    return 0;
}
