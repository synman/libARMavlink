/**
 * @file ARMAVLINK_ListUtils.h
 * @brief ARMavlink library List Utils
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_LIST_UTILS_H
#define _ARMAVLINK_LIST_UTILS_H

#include <mavlink/common/mavlink.h>

/**
 * @brief a list of waypoints.
 * @warning the list allocates first a small amount of memory. Then, when you add too much points, it will reallocate memory.
 * @see mavlink_mission_item_t
 */
typedef struct waypoint_list_t waypoint_list_t;

/**
 * @brief Create a new waypoint list
 * @warning This function allocate memory
 * @post ARMAVLINK_Utils_WaypointListDelete() must be called to delete the list and free the memory allocated.
 * @return Pointer on the new list
 * @see ARMAVLINK_Utils_WaypointListNew()
 */
waypoint_list_t* ARMAVLINK_ListUtils_WaypointListNew(void);

/**
 * @brief Get a waypoint in the list according to its index
 * @param list : a pointer on the list
 * @param[in] the index of the waypoint to return
 * @retval a pointer on the waypoint if it exists, otherwise null 
 * @see mavlink_mission_item_t in mavlink_msg_mission_item.h
 */
mavlink_mission_item_t* ARMAVLINK_ListUtils_WaypointListGet(const waypoint_list_t *const list, const uint16_t index);

/**
 * @brief Get the current size of the list (the number of waypoints which are actually in the list)
 * @param list : a pointer on the list
 * @retval the size of the list
 */
int ARMAVLINK_ListUtils_WaypointListGetSize(const waypoint_list_t *const list);

/**
 * @brief delete the list
 * @warning This function free memory
 * @param[inout] list : address of the pointer on the list
 */
void ARMAVLINK_ListUtils_WaypointListDelete(waypoint_list_t **list);

#endif
