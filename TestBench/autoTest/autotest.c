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

#include "ARMAVLINK_ListUtils.h"
#include "ARMAVLINK_WaypointUtils.h"

/* ****************************************
 *
 *             define :
 *
 **************************************** */

#define AUTOTEST_TAG "Autotest"

#define AUTOTEST_OUTPUT_FILE_PATH "output.txt"

/* ****************************************
 *
 *           variable declarations :
 *
 **************************************** */
waypoint_list_t *inWaypointList;

/* ****************************************
 *
 *           function declarations :
 *
 **************************************** */

/**
 * @brief test the utils functions
 */
eARMAVLINK_ERROR testUtils();

/**
 * @brief Create a set of waypoints and store them in inWaypointList
 */
eARMAVLINK_ERROR createTestWaypoints();

/**
 * @brief test the generation of a mavlink file based on the waypoints stored in inWaypointList
 */
eARMAVLINK_ERROR testFileGenerator();
eARMAVLINK_ERROR addWaypointsToFileGenerator(ARMAVLINK_FileGenerator_t *fileGenerator);

/**
 * @brief test the parsing of the mavlink file written in the function testFileGenerator
 */
eARMAVLINK_ERROR testFileParser();


/*****************************************
 *
 *          implementation :
 *
 *****************************************/

int main(int argc, char *argv[])
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    error = testUtils();
    fprintf(stderr, "Utils test : %s\n", ARMAVLINK_Error_ToString(error));
    
    if (error == ARMAVLINK_OK)
    {
        error = createTestWaypoints();
        fprintf(stderr, "Create test waypoint : %s\n", ARMAVLINK_Error_ToString(error));
    }
    
    if (error == ARMAVLINK_OK)
    {
        error = testFileGenerator();
        fprintf(stderr, "File Generator test : %s\n", ARMAVLINK_Error_ToString(error));
    }

    if (error == ARMAVLINK_OK)
    {
        error = testFileParser();
        fprintf(stderr, "File Parser test : %s\n", ARMAVLINK_Error_ToString(error));
    }
    
    fprintf(stderr, "Sum up : %s\n", ARMAVLINK_Error_ToString(error));
    
    return 0;
}

eARMAVLINK_ERROR testUtils()
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    // create items to add in the list
    mavlink_mission_item_t item1;
    item1.param1            = 0.11f;
    item1.param2            = 0.12f;
    item1.param3            = 0.13f;
    item1.param4            = 0.14f;
    item1.x                 = 0.15f;
    item1.y                 = 0.16f;
    item1.z                 = 0.17f;
    item1.seq               = 11;
    item1.command           = 12;
    item1.target_system     = 13;
    item1.target_component  = 14;
    item1.frame             = 15;
    item1.current           = 16;
    item1.autocontinue      = 17;
    
    mavlink_mission_item_t item2;
    item2.param1            = 0.21f;
    item2.param2            = 0.22f;
    item2.param3            = 0.23f;
    item2.param4            = 0.24f;
    item2.x                 = 0.25f;
    item2.y                 = 0.26f;
    item2.z                 = 0.27f;
    item2.seq               = 21;
    item2.command           = 22;
    item2.target_system     = 23;
    item2.target_component  = 24;
    item2.frame             = 25;
    item2.current           = 26;
    item2.autocontinue      = 27;
    
    mavlink_mission_item_t item3;
    item3.param1            = 0.31f;
    item3.param2            = 0.32f;
    item3.param3            = 0.33f;
    item3.param4            = 0.34f;
    item3.x                 = 0.35f;
    item3.y                 = 0.36f;
    item3.z                 = 0.37f;
    item3.seq               = 31;
    item3.command           = 32;
    item3.target_system     = 33;
    item3.target_component  = 34;
    item3.frame             = 35;
    item3.current           = 36;
    item3.autocontinue      = 37;
    
    mavlink_mission_item_t item4;
    item4.param1            = 0.31f;
    item4.param2            = 0.32f;
    item4.param3            = 0.33f;
    item4.param4            = 0.34f;
    item4.x                 = 0.35f;
    item4.y                 = 0.36f;
    item4.z                 = 0.37f;
    item4.seq               = 31;
    item4.command           = 32;
    item4.target_system     = 33;
    item4.target_component  = 34;
    item4.frame             = 35;
    item4.current           = 36;
    item4.autocontinue      = 37;
    
    waypoint_list_t *list = ARMAVLINK_ListUtils_WaypointListNew();
    if (list == NULL)
    {
        error = ARMAVLINK_ERROR_ALLOC;
    }
    
    if (error == ARMAVLINK_OK)
    {
        // list = [item1]
        ARMAVLINK_ListUtils_WaypointListAdd(list, &item1);
        if ((ARMAVLINK_ListUtils_WaypointListGetSize(list) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item1, ARMAVLINK_ListUtils_WaypointListGet(list, 0)) != 1))
        {
            error = ARMAVLINK_ERROR_LIST_UTILS;
        }
    }
    
    if (error == ARMAVLINK_OK)
    {
        // list = [item2, item1]
        ARMAVLINK_ListUtils_WaypointListInsertWaypoint(list, &item2, 0);
        if ((ARMAVLINK_ListUtils_WaypointListGetSize(list) != 2) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item2, ARMAVLINK_ListUtils_WaypointListGet(list, 0)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item1, ARMAVLINK_ListUtils_WaypointListGet(list, 1)) != 1))
        {
            error = ARMAVLINK_ERROR_LIST_UTILS;
        }

    }
    
    if (error == ARMAVLINK_OK)
    {
        // list = [item2, item1, item3]
        ARMAVLINK_ListUtils_WaypointListInsertWaypoint(list, &item3, 2);
        if ((ARMAVLINK_ListUtils_WaypointListGetSize(list) != 3) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item2, ARMAVLINK_ListUtils_WaypointListGet(list, 0)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item1, ARMAVLINK_ListUtils_WaypointListGet(list, 1)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item3, ARMAVLINK_ListUtils_WaypointListGet(list, 2)) != 1))
        {
            error = ARMAVLINK_ERROR_LIST_UTILS;
        }
        
    }
    
    if (error == ARMAVLINK_OK)
    {
        // list = [item2, item1, item4, item3]
        ARMAVLINK_ListUtils_WaypointListInsertWaypoint(list, &item4, 2);
        if ((ARMAVLINK_ListUtils_WaypointListGetSize(list) != 4) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item2, ARMAVLINK_ListUtils_WaypointListGet(list, 0)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item1, ARMAVLINK_ListUtils_WaypointListGet(list, 1)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item4, ARMAVLINK_ListUtils_WaypointListGet(list, 2)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item3, ARMAVLINK_ListUtils_WaypointListGet(list, 3)) != 1))
        {
            error = ARMAVLINK_ERROR_LIST_UTILS;
        }
        
    }
    
    if (error == ARMAVLINK_OK)
    {
        // list = [item2, item4, item3]
        ARMAVLINK_ListUtils_WaypointListDeleteWaypoint(list, 1);
        if ((ARMAVLINK_ListUtils_WaypointListGetSize(list) != 3) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item2, ARMAVLINK_ListUtils_WaypointListGet(list, 0)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item4, ARMAVLINK_ListUtils_WaypointListGet(list, 1)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item3, ARMAVLINK_ListUtils_WaypointListGet(list, 2)) != 1))
        {
            error = ARMAVLINK_ERROR_LIST_UTILS;
        }
        
    }
    
    if (error == ARMAVLINK_OK)
    {
        // list = [item2, item1, item3]
        ARMAVLINK_ListUtils_WaypointListReplaceWaypoint(list, &item1, 1);
        if ((ARMAVLINK_ListUtils_WaypointListGetSize(list) != 3) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item2, ARMAVLINK_ListUtils_WaypointListGet(list, 0)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item1, ARMAVLINK_ListUtils_WaypointListGet(list, 1)) != 1) ||
            (ARMAVLINK_WaypointUtils_WaypointsAreEquals(&item3, ARMAVLINK_ListUtils_WaypointListGet(list, 2)) != 1))
        {
            error = ARMAVLINK_ERROR_LIST_UTILS;
        }
        
    }
    
    return error;
}

eARMAVLINK_ERROR createTestWaypoints()
{
    mavlink_mission_item_t waypoint;
    
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    inWaypointList = ARMAVLINK_ListUtils_WaypointListNew();
    if (inWaypointList == NULL)
    {
        error = ARMAVLINK_ERROR_ALLOC;
    }
    
    // waypoint 1
    if (ARMAVLINK_OK == error)
    {
        error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, 2.367990, 48.879007, 3.0, 0, MAV_CMD_NAV_WAYPOINT, 0);
        ARMAVLINK_ListUtils_WaypointListAdd(inWaypointList, &waypoint);
    }
    
    // waypoint 2
    if (ARMAVLINK_OK == error)
    {
        error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, 2.367467, 48.878931, 3.0, 0, MAV_CMD_NAV_WAYPOINT, 1);
        ARMAVLINK_ListUtils_WaypointListAdd(inWaypointList, &waypoint);
    }
    
    // waypoint 3
    if (ARMAVLINK_OK == error)
    {
        error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, 2.367518, 48.878800, 3.0, 0, MAV_CMD_NAV_WAYPOINT, 2);
        ARMAVLINK_ListUtils_WaypointListAdd(inWaypointList, &waypoint);
    }
    
    // waypoint 4
    if (ARMAVLINK_OK == error)
    {
        error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, 2.368044, 48.878770, 3.0, 0, MAV_CMD_NAV_WAYPOINT, 3);
        ARMAVLINK_ListUtils_WaypointListAdd(inWaypointList, &waypoint);
    }
    
    // waypoint 5
    if (ARMAVLINK_OK == error)
    {
        error = ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(&waypoint, 2.367990, 48.879007, 3.0, 0, MAV_CMD_NAV_WAYPOINT, 4);
        ARMAVLINK_ListUtils_WaypointListAdd(inWaypointList, &waypoint);
    }
    
    return error;
}

eARMAVLINK_ERROR testFileGenerator()
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    ARMAVLINK_Manager_t *managerPtr = ARMAVLINK_Manager_New(&error);
    if(error == ARMAVLINK_OK)
    {
        ARMAVLINK_FileGenerator_t *fileGenerator = ARMAVLINK_FileGenerator_New(&error);
        if(error == ARMAVLINK_OK)
        {
            error = addWaypointsToFileGenerator(fileGenerator);
            
            if(error == ARMAVLINK_OK)
            {
                ARMAVLINK_FileGenerator_CreateMavlinkFile(fileGenerator, AUTOTEST_OUTPUT_FILE_PATH);
            }
            
            ARMAVLINK_FileGenerator_Delete(&fileGenerator);
        }
        else
        {
            // if there was an error in creating a new file generator
            ARMAVLINK_FileGenerator_Delete(&fileGenerator);
        }
        
        
        ARMAVLINK_Manager_Delete(&managerPtr);
    }
    else
    {
        // if there was an error in creating a new manager
        ARMAVLINK_Manager_Delete(&managerPtr);
    }

    return error;
}

eARMAVLINK_ERROR addWaypointsToFileGenerator(ARMAVLINK_FileGenerator_t *fileGenerator)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    mavlink_mission_item_t *waypoint;
    
    int i;
    int nbPointInList = ARMAVLINK_ListUtils_WaypointListGetSize(inWaypointList);

    // add all waypoints of inWaypointList
    for (i = 0; (ARMAVLINK_OK == error) && (i < nbPointInList); i++)
    {
        waypoint = ARMAVLINK_ListUtils_WaypointListGet(inWaypointList, i);
        error = ARMAVLINK_FileGenerator_AddWaypoint(fileGenerator, waypoint->x, waypoint->y, waypoint->z, waypoint->param4, waypoint->command);
    }
    
    return error;
}

eARMAVLINK_ERROR testFileParser()
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    ARMAVLINK_FileParser_t *fileParser = ARMAVLINK_FileParser_New(&error);
    if(error == ARMAVLINK_OK)
    {
        waypoint_list_t *outWaypointList = ARMAVLINK_ListUtils_WaypointListNew();
        if (outWaypointList == NULL)
        {
            error = ARMAVLINK_ERROR_ALLOC;
        }
        
        if (error == ARMAVLINK_OK)
        {
            error = ARMAVLINK_FileParser_Parse(fileParser, AUTOTEST_OUTPUT_FILE_PATH, outWaypointList);
        }
        
        if (error == ARMAVLINK_OK)
        {
            int i;
            int nbPointInList = ARMAVLINK_ListUtils_WaypointListGetSize(outWaypointList);
            if (nbPointInList != ARMAVLINK_ListUtils_WaypointListGetSize(inWaypointList))
            {
                error = ARMAVLINK_ERROR_FILE_PARSER;
                fprintf(stderr, "The list to write and the list to parse do not have the same size\n");
            }
            
            for (i = 0; (ARMAVLINK_OK == error) && (i < nbPointInList); i++)
            {
                mavlink_mission_item_t *outWaypoint = ARMAVLINK_ListUtils_WaypointListGet(outWaypointList, i);
                mavlink_mission_item_t *inWaypoint = ARMAVLINK_ListUtils_WaypointListGet(inWaypointList, i);
                
                if (ARMAVLINK_WaypointUtils_WaypointsAreEquals(inWaypoint, outWaypoint) != 1)
                {
                    error = ARMAVLINK_ERROR_FILE_PARSER;
                    fprintf(stderr, "The waypoint %i of the list to write and the parsed are not the same\n", i);
                }
            }
        }
        
        ARMAVLINK_FileParser_Delete(&fileParser);
    }
    else
    {
        // if there was an error in creating a new file parser
        ARMAVLINK_FileParser_Delete(&fileParser);
    }
    
    return error;
}
