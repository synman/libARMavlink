/**
 * @file ARMAVLINK_FileParser.h
 * @brief Mavlink File Parser
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_FILEPARSER_h
#define _ARMAVLINK_FILEPARSER_h

#include <libARMavlink/ARMAVLINK_Error.h>
#include <libARMavlink/ARMAVLINK_ListUtils.h>
#include <mavlink/common/mavlink.h>

/**
 * @brief ARMavlink file parser structure allows to manage the process of parsing Mavlink files
 */
typedef struct ARMAVLINK_FileParser_t ARMAVLINK_FileParser_t;


/**
 * @brief Create a new file parser
 * @warning This function allocate memory
 * @post ARMAVLINK_FileParser_Delete() must be called to delete the file parser and free the memory allocated.
 * @param[out] error : pointer on the error output.
 * @return Pointer on the new file parser
 * @see ARMAVLINK_FileParser_Delete()
 */
ARMAVLINK_FileParser_t* ARMAVLINK_FileParser_New(eARMAVLINK_ERROR *error);

/**
 * @brief Delete the File parser
 * @warning This function free memory
 * @param fileParser : address of the pointer on the file parser
 * @see ARMAVLINK_FileParser_New()
 */
void ARMAVLINK_FileParser_Delete(ARMAVLINK_FileParser_t **fileParser);

/**
 * @brief Parse a Mavlink file and store it in a list
 * @param fileParser : pointer on the file parser
 * @param[in] filePath : the path of the file to parse
 * @param[out] waypointList : a list of all waypoints
 * @return ARMAVLINK_OK if parsing went well, the enum description of the error otherwise
 * @see waypoint_list_t
 */
eARMAVLINK_ERROR ARMAVLINK_FileParser_Parse(ARMAVLINK_FileParser_t *fileParser, const char *const filePath, waypoint_list_t *waypointList);


#endif
