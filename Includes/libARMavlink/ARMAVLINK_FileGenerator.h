/**
 * @file ARMAVLINK_FileGenerator.h
 * @brief Mavlink File Generator
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_FILEGENERATOR_h
#define _ARMAVLINK_FILEGENERATOR_h

#include <libARMavlink/ARMAVLINK_Error.h>
#include <libARMavlink/ARMAVLINK_ListUtils.h>
#include <libmavlink/common/mavlink.h>

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
 * @brief Add a mission item to the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] missionItem : the mission item to add
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_AddMissionItem(ARMAVLINK_FileGenerator_t *fileGenerator, mavlink_mission_item_t *missionItem);

/**
 * @brief Replace a mission item in the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] missionItem : the mission item to replace with
 * @param[in] index : the index of the mission item to replace
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_ReplaceMissionItem(ARMAVLINK_FileGenerator_t *fileGenerator, mavlink_mission_item_t *missionItem, int index);

/**
 * @brief Insert a mission item in the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] missionItem : the mission item to insert.
 * @param[in] index : the index of the mission item to replace
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_InsertMissionItem(ARMAVLINK_FileGenerator_t *fileGenerator, mavlink_mission_item_t *missionItem, int index);

/**
 * @brief Delete a mission item in the File Generator list
 * @param fileGenerator : pointer on the file generator
 * @param[in] index : the index of the mission item to delete
 * @return ARMAVLINK_OK if operation went well, the enum description of the error otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_DeleteMissionItem(ARMAVLINK_FileGenerator_t *fileGenerator, int index);

/**
 * @brief Write a mavlink file with all the mission items in the list
 * @param fileGenerator : pointer on the file generator
 * @param[in] filePath : path to write the file
 */
void ARMAVLINK_FileGenerator_CreateMavlinkFile(ARMAVLINK_FileGenerator_t *fileGenerator, const char *const filePath);

/**
 * @brief Get the current mission item list
 * @param fileGenerator : pointer on the file generator
 * @param[out] err : pointer on the error output. Can be null
 * @return the mission item list
*/
mission_item_list_t *ARMAVLINK_FileGenerator_GetCurrentMissionItemList(ARMAVLINK_FileGenerator_t *fileGenerator, eARMAVLINK_ERROR *err);
#endif
