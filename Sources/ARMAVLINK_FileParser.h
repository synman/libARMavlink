/**
 * @file ARMAVLINK_FileParser.h
 * @brief Mavlink File Parser
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_FILE_PARSER_PRIVATE_H
#define _ARMAVLINK_FILE_PARSER_PRIVATE_H

#include <libARMavlink/ARMAVLINK_FileParser.h>
#include <libARMavlink/ARMAVLINK_Error.h>
#include "ARMAVLINK_ListUtils.h"

/**
 * @brief ARMavlink file parser structure allows to manage the process of reading Mavlink files
 */
struct ARMAVLINK_FileParser_t
{
    char *mavlinkVersion;
};

/**
 * @brief Read the first line of the mavlink file
 * @param fileParser : Pointer on the file parser
 * @param[in|out] line : the first line
 * @warning : the line param will be modified by this function
 */
eARMAVLINK_ERROR ARMAVLINK_FileParser_ReadFirstLine(ARMAVLINK_FileParser_t *fileParser, char *line);

/**
 * @brief Read a mavlink command and add the command to the waypoint list
 * @param fileParser : Pointer on the file parser
 * @param[in|out] line : the line
 * @param[out] waypointList : the list to add the waypoint
 * @warning : the line param will be modified by this function
 */
eARMAVLINK_ERROR ARMAVLINK_FileParser_ReadMavlinkCommand(ARMAVLINK_FileParser_t *fileParser, char *line, waypoint_list_t *waypointList);

#endif
