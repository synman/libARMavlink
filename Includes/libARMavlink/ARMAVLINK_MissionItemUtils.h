/**
 * @file ARMAVLINK_MissionItemUtils.h
 * @brief Mavlink Mission item utils
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_MISSIONITEMUTILS_h
#define _ARMAVLINK_MISSIONITEMUTILS_h

#include <libARMavlink/ARMAVLINK_Error.h>
#include <libmavlink/common/mavlink.h>

/**
 * @brief Fill a mission item with the given params and the default params
 * @param[out] missionItem : pointer on the mission item to fill
 * @param[in] param1 : Radius in which the MISSION is accepted as reached, in meters
 * @param[in] param2 : Time that the MAV should stay inside the PARAM1 radius before advancing, in milliseconds
 * @param[in] param3 : For LOITER command MISSIONs: Orbit to circle around the MISSION, in meters. If positive the orbit direction should be clockwise, if negative the orbit direction should be counter-clockwise.
 * @param4[in] : For NAV and LOITER command MISSIONs: Yaw orientation in degrees, [0..360] 0 = NORTH
 * @param[in] latitude : the latitude of the mission item
 * @param[in] latitude : the latitude of the mission item
 * @param[in] longitude : the longitude of the mission item
 * @param[in] altitude : the altitude of the mission item
 * @param[in] command : the command of the mission item
 * @param[in] seq : the seq of the mission item
 * @param[in] frame : The coordinate system of the MISSION. see MAV_FRAME in mavlink_types.h
 * @param[in] current : false:0, true:1
 * @param[in] autocontinue : autocontinue to next wp
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkMissionItemWithAllParams(mavlink_mission_item_t* missionItem, float param1, float param2, float param3, float param4, float latitude, float longitude, float altitude, int command, int seq,  int frame, int current, int autocontinue);

/**
 * @brief Fill a nav mission item with the given params and the default params
 * @param[out] missionItem : pointer on the mission item to fill
 * @param[in] latitude : the latitude of the mission item
 * @param[in] longitude : the longitude of the mission item
 * @param[in] altitude : the altitude of the mission item
 * @param[in] yaw : the yaw of the mission item
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkNavWaypointMissionItem(mavlink_mission_item_t* missionItem, float latitude, float longitude, float altitude, float yaw);

/**
 * @brief Fill a land mission item with the given params and the default params
 * @param[out] missionItem : pointer on the mission item to fill
 * @param[in] latitude : the latitude of the mission item
 * @param[in] longitude : the longitude of the mission item
 * @param[in] altitude : the altitude of the mission item
 * @param[in] yaw : the yaw of the mission item
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkLandMissionItem(mavlink_mission_item_t* missionItem, float latitude, float longitude, float altitude, float yaw);

/**
 * @brief Fill a takeoff mission item with the given params and the default params
 * @param[out] missionItem : pointer on the mission item to fill
 * @param[in] latitude : the latitude of the mission item
 * @param[in] longitude : the longitude of the mission item
 * @param[in] altitude : the altitude of the mission item
 * @param[in] yaw : the yaw of the mission item
 * @param[in] pitch : desired pitch
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkTakeoffMissionItem(mavlink_mission_item_t* missionItem, float latitude, float longitude, float altitude, float yaw, float pitch);

/**
 * @brief Fill a change speed mission item with the given params and the default params
 * @param[out] missionItem : pointer on the mission item to fill
 * @param[in] groundSpeed : 1 if ground speed, 0 if airspeed
 * @param[in] speed : the speed of the mission item
 * @param[in] throttle : throttle in percent, -1 indicates no changes
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkChangeSpeedMissionItem(mavlink_mission_item_t* missionItem, int groundSpeed, float speed, float throttle);

eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkVideoStartCapture(mavlink_mission_item_t* missionItem, int cameraId, float framesPerSeconds, float resolution);

eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkVideoStopCapture(mavlink_mission_item_t* missionItem);

eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkImageStartCapture(mavlink_mission_item_t* missionItem,float period,float imagesCount,float resolution);

eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkImageStopCapture(mavlink_mission_item_t* missionItem);

eARMAVLINK_ERROR ARMAVLINK_MissionItemUtils_CreateMavlinkCreatePanorama(mavlink_mission_item_t* missionItem,float horizontalAngle,float verticalAngle,float horizontalRotationSpeed);

#endif
