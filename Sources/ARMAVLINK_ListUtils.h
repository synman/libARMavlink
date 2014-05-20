/**
 * @file ARMAVLINK_ListUtils.h
 * @brief ARMavlink library List Utils
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_LIST_UTILS_PRIVATE_H
#define _ARMAVLINK_LIST_UTILS_PRIVATE_H

#include <libARMavlink/ARMAVLINK_ListUtils.h>
#include <libARMavlink/ARMAVLINK_Error.h>
#include <mavlink/common/mavlink.h>

/**
 * @brief Add a waypoint in the list
 * @param list : a pointer on the list
 * @param[in] waypoint : a pointer on the waypoint to add
 * @retval the index of the place in the list where the point has been added
 * @warning this function copies the point. Also, if the memory allocated for the list is full, it reallocates memory to add more points
 */
uint16_t ARMAVLINK_ListUtils_WaypointListAdd(waypoint_list_t *list, const mavlink_mission_item_t *const waypoint);

/**
 * @brief delete a point in the list. Replace all following waypoints to their indexes - 1
 * @param list : the pointer on the list
 * @param[in] index : index of the waypoint to delete
 * @return ARMAVLINK_OK if the deletion went well, the enum description of the error
 */
eARMAVLINK_ERROR ARMAVLINK_ListUtils_WaypointListDeleteWaypoint(waypoint_list_t *list, const uint16_t index);

/**
 * @brief insert a point in the list
 * @param list : the pointer on the list
 * @param[in] waypoint : the waypoint to insert
 * @param[in] index : index of where to insert the waypoint
 * @return ARMAVLINK_OK if the insertion went well, the enum description of the error
 * @warning this function copies the point. Also, if the memory allocated for the list is full, it reallocates memory to add more points
 */
eARMAVLINK_ERROR ARMAVLINK_ListUtils_WaypointListInsertWaypoint(waypoint_list_t *list, const mavlink_mission_item_t *const waypoint, const uint16_t index);

/**
 * @brief replace a point in the list with another
 * @param list :the pointer on the list
 * @param[in] waypoint : the new waypoint which will replace the old one
 * @param[in] index : index of waypoint to replace
 * @return ARMAVLINK_OK if the replacement went well, the enum description of the error
 * @warning this function copies the point.
 */
eARMAVLINK_ERROR ARMAVLINK_ListUtils_WaypointListReplaceWaypoint(waypoint_list_t *list, const mavlink_mission_item_t *const waypoint, const uint16_t index);

#endif
