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
#include <libmavlink/common/mavlink.h>

/**
 * @brief Add a mission item in the list
 * @param list : a pointer on the list
 * @param[in] missionItem : a pointer on the mission item to add
 * @retval the index of the place in the list where the item has been added
 * @warning this function copies the point. Also, if the memory allocated for the list is full, it reallocates memory to add more points
 */
uint16_t ARMAVLINK_ListUtils_MissionItemListAdd(mission_item_list_t *list, const mavlink_mission_item_t *const missionItem);

/**
 * @brief delete a point in the list. Replace all following mission items to their indexes - 1
 * @param list : the pointer on the list
 * @param[in] index : index of the mission item to delete
 * @return ARMAVLINK_OK if the deletion went well, the enum description of the error
 */
eARMAVLINK_ERROR ARMAVLINK_ListUtils_MissionItemListDeleteMissionItem(mission_item_list_t *list, const uint16_t index);

/**
 * @brief insert a point in the list
 * @param list : the pointer on the list
 * @param[in] missionItem : the mission item to insert
 * @param[in] index : index of where to insert the mission item
 * @return ARMAVLINK_OK if the insertion went well, the enum description of the error
 * @warning this function copies the point. Also, if the memory allocated for the list is full, it reallocates memory to add more points
 */
eARMAVLINK_ERROR ARMAVLINK_ListUtils_MissionItemListInsertMissionItem(mission_item_list_t *list, const mavlink_mission_item_t *const missionItem, const uint16_t index);

/**
 * @brief replace a mission item in the list with another
 * @param list :the pointer on the list
 * @param[in] missionItem : the new mission item which will replace the old one
 * @param[in] index : index of mission item to replace
 * @return ARMAVLINK_OK if the replacement went well, the enum description of the error
 * @warning this function copies the item.
 */
eARMAVLINK_ERROR ARMAVLINK_ListUtils_MissionItemListReplaceMissionItem(mission_item_list_t *list, const mavlink_mission_item_t *const missionItem, const uint16_t index);

#endif
