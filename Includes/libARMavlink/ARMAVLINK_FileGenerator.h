/**
 * @file ARMAVLINK_FileGenerator.h
 * @brief Mavlink File Generator
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_FILEGENERATOR_h
#define _ARMAVLINK_FILEGENERATOR_h

#include <libARMavlink/ARMAVLINK_Error.h>
#include <mavlink/common/mavlink.h>

/**
 * @brief ARMavlink file generator structure allows to manage the process of creating Mavlink files
 */
typedef struct ARMAVLINK_FileGenerator_t ARMAVLINK_FileGenerator_t;

/**
 * @brief Create a new file generator
 * @warning This function allocate memory
 * @post ARMAVLINK_FileGenerator_Delete() must be called to delete the file generator and free the memory allocated.
 * @param[out] error : pointer on the error output.
 * @return Pointer on the new file generator
 * @see ARMAVLINK_FileGenerator_Delete()
 */
ARMAVLINK_FileGenerator_t* ARMAVLINK_FileGenerator_New(eARMAVLINK_ERROR *error);

/**
 * @brief Delete the File generator
 * @warning This function free memory
 * @param fileGenerator : address of the pointer on the file generator
 * @see ARMAVLINK_FileGenerator_New()
 */
void ARMAVLINK_FileGenerator_Delete(ARMAVLINK_FileGenerator_t **fileGenerator);

/**
 * @brief Add a waypoint to the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] latitude : the latitude of the waypoint
 * @param[in] longitude : the longitude of the waypoint
 * @param[in] altitude : the altitude of the waypoint
 * @param[in] yaw : the yaw of the waypoint
 * @param[in] command : the command of the waypoint (see MAV_CMD in common.h)
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_AddWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, float latitude, float longitude, float altitude, float yaw, int command);

/**
 * @brief Replace a waypoint in the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] latitude : the latitude of the waypoint
 * @param[in] longitude : the longitude of the waypoint
 * @param[in] altitude : the altitude of the waypoint
 * @param[in] yaw : the yaw of the waypoint
 * @param[in] command : the command of the waypoint (see MAV_CMD in common.h)
 * @param[in] index : the index of the waypoint to replace
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_ReplaceWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, float latitude, float longitude, float altitude, float yaw, int command, int index);

/**
 * @brief Insert a waypoint in the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] latitude : the latitude of the waypoint
 * @param[in] longitude : the longitude of the waypoint
 * @param[in] altitude : the altitude of the waypoint
 * @param[in] yaw : the yaw of the waypoint
 * @param[in] command : the command of the waypoint (see MAV_CMD in common.h)
 * @param[in] index : the index of the waypoint to replace
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_InsertWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, float latitude, float longitude, float altitude, float yaw, int command, int index);

/**
 * @brief Delete a waypoint in the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] index : the index of the waypoint to delete
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_DeleteWaypoint(ARMAVLINK_FileGenerator_t *fileGenerator, int index);

/**
 * @brief Write a mavlink file with all the waypoints in the list
 * @param fileGenerator : pointer on the file generator
 * @param[in] filePath : path to write the file
 */
void ARMAVLINK_FileGenerator_CreateMavlinkFile(ARMAVLINK_FileGenerator_t *fileGenerator, const char *const filePath);

#endif
