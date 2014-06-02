/**
 * @file ARMAVLINK_Utils.h
 * @brief ARMavlink library Utils
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_WAYPOINT_UTILS_PRIVATE_H
#define _ARMAVLINK_WAYPOINT_UTILS_PRIVATE_H

#include <libARMavlink/ARMAVLINK_Error.h>
#include <libmavlink/common/mavlink.h>

/**
 * @brief Determine if two waypoints are equals
 * @param[in] waypoint1 : one waypoint to compare
 * @param[in] waypoint2 : one waypoint to compare
 * @return 1 if the two waypoints values are equals, 0 otherwise
 */
int ARMAVLINK_WaypointUtils_WaypointsAreEquals(const mavlink_mission_item_t *const waypoint1, const mavlink_mission_item_t *const waypoint2);

/**
 * @brief Fill a waypoint with the given params and the default params
 * @param[out] waypoint : pointer on the waypoint to fill
 * @param[in] latitude : the latitude of the waypoint
 * @param[in] longitude : the longitude of the waypoint
 * @param[in] altitude : the altitude of the waypoint
 * @param[in] yaw : the yaw of the waypoint
 * @param[in] command : the command of the waypoint
 * @param[in] seq : the seq of the waypoint
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_WaypointUtils_CreateMavlinkMissionItem(mavlink_mission_item_t* waypoint, float latitude, float longitude, float altitude, float yaw, int command, int seq);

/**
 * @brief Fill a waypoint with the given params and the default params
 * @param[out] waypoint : pointer on the waypoint to fill
 * @param[in] param1 : Radius in which the MISSION is accepted as reached, in meters
 * @param[in] param2 : Time that the MAV should stay inside the PARAM1 radius before advancing, in milliseconds
 * @param[in] param3 : For LOITER command MISSIONs: Orbit to circle around the MISSION, in meters. If positive the orbit direction should be clockwise, if negative the orbit direction should be counter-clockwise.
 * @param4[in] : For NAV and LOITER command MISSIONs: Yaw orientation in degrees, [0..360] 0 = NORTH
 * @param[in] latitude : the latitude of the waypoint
 * @param[in] latitude : the latitude of the waypoint
 * @param[in] longitude : the longitude of the waypoint
 * @param[in] altitude : the altitude of the waypoint
 * @param[in] command : the command of the waypoint
 * @param[in] seq : the seq of the waypoint
 * @param[in] frame : The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
 * @param[in] current : false:0, true:1
 * @param[in] autocontinue : autocontinue to next wp
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_WaypointUtils_CreateMavlinkMissionItemWithAllParams(mavlink_mission_item_t* waypoint, float param1, float param2, float param3, float param4, float latitude, float longitude, float altitude, int command, int seq, int frame, int current, int autocontinue);

#endif
