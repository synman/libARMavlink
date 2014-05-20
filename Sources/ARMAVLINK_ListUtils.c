/**
 * @file ARMAVLINK_ListUtils.c
 * @brief ARMavlink library List Utils
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#include <stdlib.h>
#include "ARMAVLINK_ListUtils.h"

/* ****************************************
 *
 *             define :
 *
 **************************************** */
#define ARMAVLINK_LIST_UTILS_TAG                "ARMAVLINK_ListUtils"
#define ARMAVLINK_LIST_UTILS_LIST_SIZE          32
#define ARMAVLINK_LIST_UTILS_LIST_MAX_INDEX     ((uint16_t) -1)

struct waypoint_list_t
{
    int size;
    int alloc_size;
    mavlink_mission_item_t *waypoints;
};

waypoint_list_t* ARMAVLINK_ListUtils_WaypointListNew(void)
{
    waypoint_list_t *list = (waypoint_list_t *)malloc(sizeof(waypoint_list_t));
    if(list != NULL)
    {
        list->waypoints = (mavlink_mission_item_t *)malloc(sizeof(mavlink_mission_item_t) * ARMAVLINK_LIST_UTILS_LIST_SIZE);
        if(list->waypoints != NULL)
        {
            list->alloc_size = ARMAVLINK_LIST_UTILS_LIST_SIZE;
            list->size = 0;
        }
        else
        {
            free(list);
            list = NULL;
        }
    }
    
    return list;
}

uint16_t ARMAVLINK_ListUtils_WaypointListAdd(waypoint_list_t *list, const mavlink_mission_item_t *const waypoint)
{
    uint16_t index = ARMAVLINK_LIST_UTILS_LIST_MAX_INDEX;
    
    if(list != NULL && waypoint != NULL)
    {
        if(list->size == list->alloc_size)
        {
            list->alloc_size += ARMAVLINK_LIST_UTILS_LIST_SIZE;
            mavlink_mission_item_t *new_points = (mavlink_mission_item_t *)realloc(list->waypoints, sizeof(mavlink_mission_item_t) * list->alloc_size);
            if(new_points != NULL)
            {
                list->waypoints = new_points;
            }
        }
        
        index = list->size;
        memcpy(&(list->waypoints[index]), waypoint, sizeof(mavlink_mission_item_t));
        list->size++;
    }
    
    return index;
}

mavlink_mission_item_t* ARMAVLINK_ListUtils_WaypointListGet(const waypoint_list_t *const list, const uint16_t index)
{
    mavlink_mission_item_t *retval = NULL;
    if(list != NULL && index < list->size && index >= 0)
    {
        retval = &list->waypoints[index];
    }
    
    return retval;
}

int ARMAVLINK_ListUtils_WaypointListGetSize(const waypoint_list_t *const list)
{
    return list->size;
}

eARMAVLINK_ERROR ARMAVLINK_ListUtils_WaypointListDeleteWaypoint(waypoint_list_t *list, const uint16_t index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if ((list != NULL) &&
        (index < list->size) &&
        (index >= 0))
    {
        int nbWaypointsToCopy = (list->size - index) - 1;
        if (nbWaypointsToCopy > 0)
        {
            memcpy(&(list->waypoints[index]), &(list->waypoints[index+1]), nbWaypointsToCopy * sizeof(mavlink_mission_item_t));
        }
        list->size--;
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;
}

eARMAVLINK_ERROR ARMAVLINK_ListUtils_WaypointListInsertWaypoint(waypoint_list_t *list, const mavlink_mission_item_t *const waypoint, const uint16_t index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if ((list != NULL) &&
        (index <= list->size) &&
        (index >= 0) &&
        (waypoint != NULL))
    {
        if(list->size == list->alloc_size)
        {
            list->alloc_size += ARMAVLINK_LIST_UTILS_LIST_SIZE;
            mavlink_mission_item_t *new_points = (mavlink_mission_item_t *)realloc(list->waypoints, sizeof(mavlink_mission_item_t) * list->alloc_size);
            if(new_points != NULL)
            {
                list->waypoints = new_points;
            }
        }
        
        int nbWaypointsToCopy = (list->size - index);
        if (nbWaypointsToCopy > 0)
        {
            memcpy(&(list->waypoints[index+1]), &(list->waypoints[index]), nbWaypointsToCopy * sizeof(mavlink_mission_item_t));
        }
        memcpy(&(list->waypoints[index]), waypoint, sizeof(mavlink_mission_item_t));
        list->size++;
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;

}

eARMAVLINK_ERROR ARMAVLINK_ListUtils_WaypointListReplaceWaypoint(waypoint_list_t *list, const mavlink_mission_item_t *const waypoint, const uint16_t index)
{
    eARMAVLINK_ERROR error = ARMAVLINK_OK;
    
    if ((list != NULL) &&
        (index <= list->size) &&
        (index >= 0) &&
        (waypoint != NULL))
    {
        memcpy(&(list->waypoints[index]), waypoint, sizeof(mavlink_mission_item_t));
    }
    else
    {
        error = ARMAVLINK_ERROR_BAD_PARAMETER;
    }
    
    return error;
}

void ARMAVLINK_ListUtils_WaypointListDelete(waypoint_list_t **list)
{
    waypoint_list_t *listPtr = NULL;
    
    if (list)
    {
        listPtr = *list;
        
        if (listPtr)
        {
            if(listPtr->waypoints != NULL)
            {
                free(listPtr->waypoints);
                listPtr->waypoints = NULL;
            }
            
            free (listPtr);
            listPtr = NULL;
        }
        
        *list = NULL;
    }
}

