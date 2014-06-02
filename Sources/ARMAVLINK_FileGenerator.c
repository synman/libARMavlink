/**
 * @file ARMAVLINK_FileGenerator.c
 * @brief Mavlink File Generator
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#include <stdlib.h>
#include <stdio.h>
#include <libARSAL/ARSAL_Print.h>
#include "ARMAVLINK_FileGenerator.h"
#include "ARMAVLINK_WaypointUtils.h"

/* ***************************************
 *
 *             define :
 *
 *****************************************/
#define ARMAVLINK_FILE_GENERATOR_TAG                                "ARMAVLINK_FileGenerator"

#define ARMAVLINK_FILE_GENERATOR_FILE_HEADER                        "QGC WPL 120"

/* ***************************************
 *
 *             functions :
 *
 *****************************************/

ARMAVLINK_FileGenerator_t* ARMAVLINK_FileGenerator_New(eARMAVLINK_ERROR *error)
{
    ARMAVLINK_FileGenerator_t *fileGenerator = NULL;
    eARMAVLINK_ERROR err = ARMAVLINK_OK;
    
    /* Check parameters */
    if(err == ARMAVLINK_OK)
    {
        /* Create the file generator */
        fileGenerator = malloc (sizeof (ARMAVLINK_FileGenerator_t));
        if (fileGenerator == NULL)
        {
            err = ARMAVLINK_ERROR_ALLOC;
        }
    }
    
    if(err == ARMAVLINK_OK)
    {
        fileGenerator->waypointList = ARMAVLINK_ListUtils_WaypointListNew();
        if (fileGenerator->waypointList == NULL)
        {
            err = ARMAVLINK_ERROR_ALLOC;
        }
    }
    
    /* delete the file generator if an error occurred */
    if (err != ARMAVLINK_OK)
    {
        ARSAL_PRINT (ARSAL_PRINT_ERROR, ARMAVLINK_FILE_GENERATOR_TAG, "error: %s", ARMAVLINK_Error_ToString (err));
        ARMAVLINK_FileGenerator_Delete (&fileGenerator);
    }
    
    /* return the error */
    if (error != NULL)
    {
        *error = err;
    }
    
    return fileGenerator;
}

void ARMAVLINK_FileGenerator_Delete(ARMAVLINK_FileGenerator_t **fileGenerator)
{
    ARMAVLINK_FileGenerator_t *fileGeneratorPtr = NULL;
    
    if (fileGenerator)
    {
        fileGeneratorPtr = *fileGenerator;
        
        // Uninitialize here
        ARMAVLINK_ListUtils_WaypointListDelete(&fileGeneratorPtr->waypointList);
        
        
        if (fileGeneratorPtr)
        {
            free (fileGeneratorPtr);
            fileGeneratorPtr = NULL;
        }
        
        *fileGenerator = NULL;
    }
}

eARMAVLINK_ERROR ARMAVLINK_FileGenerator_AddWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, float latitude, float longitude, float altitude, float yaw, int command)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    mavlink_mission_item_t waypoint;
    int seq = ARMAVLINK_ListUtils_WaypointListGetSize(fileGenerator->waypointList);
    error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, latitude, longitude, altitude, yaw, command, seq);
    if (error == ARMAVLINK_OK)
    {
        ARMAVLINK_ListUtils_WaypointListAdd(fileGenerator->waypointList, &waypoint);
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_FileGenerator_ReplaceWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, float latitude, float longitude, float altitude, float yaw, int command, int index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    mavlink_mission_item_t waypoint;
    int seq = index;
    error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, latitude, longitude, altitude, yaw, command, seq);
    if (error == ARMAVLINK_OK)
    {
        ARMAVLINK_ListUtils_WaypointListReplaceWaypoint(fileGenerator->waypointList, &waypoint, index);
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_FileGenerator_InsertWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, float latitude, float longitude, float altitude, float yaw, int command, int index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    mavlink_mission_item_t waypoint;
    int seq = index;
    error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, latitude, longitude, altitude, yaw, command, seq);
    if (error == ARMAVLINK_OK)
    {
        ARMAVLINK_ListUtils_WaypointListInsertWaypoint(fileGenerator->waypointList, &waypoint, index);
        ARMAVLINK_FileGenerator_ResetSequences(fileGenerator->waypointList, index+1);
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_FileGenerator_DeleteWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, int index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;

    error = ARMAVLINK_ListUtils_WaypointListDeleteWaypoint(fileGenerator->waypointList, index);
    ARMAVLINK_FileGenerator_ResetSequences(fileGenerator->waypointList, index);
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_FileGenerator_ResetSequences(waypoint_list_t *list, int startIndex)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    int i;
    int size = ARMAVLINK_ListUtils_WaypointListGetSize(list);
    for (i = startIndex; i < size; i++)
    {
        mavlink_mission_item_t *waypoint = ARMAVLINK_ListUtils_WaypointListGet(list, i);
        waypoint->seq = i;
    }
    
    return error;
}


void ARMAVLINK_FileGenerator_CreateMavlinkFile(ARMAVLINK_FileGenerator_t *fileGenerator, const char *const filePath)
{
    // open the file
    FILE *file;
    file = fopen(filePath,"w");
    
    fprintf(file, "%s\n", ARMAVLINK_FILE_GENERATOR_FILE_HEADER);
    
    int waypointIdx = 0;
    int waypointCount = ARMAVLINK_ListUtils_WaypointListGetSize(fileGenerator->waypointList);
    for (waypointIdx = 0; waypointIdx < waypointCount; waypointIdx++)
    {
        mavlink_mission_item_t *waypoint = ARMAVLINK_ListUtils_WaypointListGet(fileGenerator->waypointList, waypointIdx);
        // <INDEX> <CURRENT WP> <COORD FRAME> <COMMAND> <PARAM1> <PARAM2> <PARAM3> <PARAM4> <PARAM5/X/LONGITUDE> <PARAM6/Y/LATITUDE> <PARAM7/Z/ALTITUDE> <AUTOCONTINUE>
        // where each space is a tabulation
        fprintf(file, "%i\t%i\t%i\t%i\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%i\n",
                waypoint->seq,
                waypoint->current,
                waypoint->frame,
                waypoint->command,
                waypoint->param1,
                waypoint->param2,
                waypoint->param3,
                waypoint->param4,
                waypoint->x,
                waypoint->y,
                waypoint->z,
                waypoint->autocontinue);
    }
    fclose(file);
}





























