/**
 * @file ARMAVLINK_WaypointUtils.c
 * @brief ARMavlink library Utils about waypoints
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#include <stdlib.h>
#include "ARMAVLINK_WaypointUtils.h"

// default waypoint values
#define ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_RADIUS            0.0f    // in meters
#define ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TIME              0.0f    // in ms
#define ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_ORBIT             0.0f
#define ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TARGET_SYSTEM     1
#define ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TARGET_COMPONENT  1
#define ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_AUTOCONTINUE      1
#define ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_POSITION_REFENTIAL MAV_FRAME_GLOBAL_RELATIVE_ALT // in common.h

int ARMAVLINK_WaypointUtils_WaypointsAreEquals(const mavlink_mission_item_t *const waypoint1, const mavlink_mission_item_t *const waypoint2)
{
    int equal = 0;
    
    if ((waypoint1->param1 == waypoint2->param1) &&
        (waypoint1->param2 == waypoint2->param2) &&
        (waypoint1->param3 == waypoint2->param3) &&
        (waypoint1->param4 == waypoint2->param4) &&
        (waypoint1->x == waypoint2->x) &&
        (waypoint1->y == waypoint2->y) &&
        (waypoint1->z == waypoint2->z) &&
        (waypoint1->seq == waypoint2->seq) &&
        (waypoint1->command == waypoint2->command) &&
        (waypoint1->target_system == waypoint2->target_system) &&
        (waypoint1->target_component == waypoint2->target_component) &&
        (waypoint1->frame == waypoint2->frame) &&
        (waypoint1->current == waypoint2->current) &&
        (waypoint1->autocontinue == waypoint2->autocontinue))
    {
        equal = 1;
    }
    
    return equal;
    
}

eARMAVLINK_ERROR ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(mavlink_mission_item_t* waypoint, float latitude, float longitude, float altitude, float yaw, int command, int seq)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if (waypoint != NULL)
    {
        waypoint->param1            = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_RADIUS;
        waypoint->param2            = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TIME;
        waypoint->param3            = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_ORBIT;
        waypoint->param4            = yaw;
        waypoint->x                 = latitude;
        waypoint->y                 = longitude;
        waypoint->z                 = altitude;
        waypoint->seq               = seq;
        waypoint->command           = command;
        waypoint->target_system     = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TARGET_SYSTEM;
        waypoint->target_component  = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TARGET_COMPONENT;
        waypoint->frame             = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_POSITION_REFENTIAL;
        if (seq == 0)
        {
            waypoint->current       = 1;
        }
        else
        {
            waypoint->current       = 0;
        }
        
        waypoint->autocontinue      = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_AUTOCONTINUE;
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_WaypointUtils_CreateMavlinkMissionItemWithAllParams(mavlink_mission_item_t* waypoint, float param1, float param2, float param3, float param4, float latitude, float longitude, float altitude, int command, int seq, int frame, int current, int autocontinue)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if (waypoint != NULL)
    {
        waypoint->param1            = param1;
        waypoint->param2            = param2;
        waypoint->param3            = param3;
        waypoint->param4            = param4;
        waypoint->x                 = latitude;
        waypoint->y                 = longitude;
        waypoint->z                 = altitude;
        waypoint->seq               = seq;
        waypoint->command           = command;
        waypoint->target_system     = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TARGET_SYSTEM;
        waypoint->target_component  = ARMAVLINK_WAYPOINT_UTILS_WAYPOINT_DEFAULT_TARGET_COMPONENT;
        waypoint->frame             = frame;
        waypoint->current           = current;
        waypoint->autocontinue      = autocontinue;
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;
}