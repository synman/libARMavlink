/**
 * @file ARMAVLINK_MissionItemUtils.h
 * @brief ARMavlink library Utils
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_MISSION_ITEM_UTILS_PRIVATE_H
#define _ARMAVLINK_MISSION_ITEM_UTILS_PRIVATE_H

#include <libARMavlink/ARMAVLINK_MissionItemUtils.h>
#include <libARMavlink/ARMAVLINK_Error.h>
#include <libmavlink/common/mavlink.h>

/**
 * @brief Determine if two mission items are equals
 * @param[in] missionItem1 : one mission item to compare
 * @param[in] missionItem2 : one mission item to compare
 * @return 1 if the two mission items values are equals, 0 otherwise
 */
int ARMAVLINK_MissionItemUtils_MissionItemsAreEquals(const mavlink_mission_item_t *const missionItem1, const mavlink_mission_item_t *const missionItem2);

/**
 * @brief Copy a mavlink item in an other one
 * @param[out] missionItemCpy : the copy of the mission item. It should be allocated
 * @param[in] missionItem : the mission item to copy
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CopyMavlinkMissionItem(mavlink_mission_item_t * missionItemCpy, const mavlink_mission_item_t *const missionItem);


#endif
