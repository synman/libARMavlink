/**
 * @file ARMAVLINK_FileGenerator.h
 * @brief Mavlink File Generator
 * @date 14/05/2014
 * @author djavan.bertrand@parrot.com
 */
#ifndef _ARMAVLINK_FILE_GENERATOR_PRIVATE_H
#define _ARMAVLINK_FILE_GENERATOR_PRIVATE_H

#include <libARMavlink/ARMAVLINK_FileGenerator.h>
#include <libARMavlink/ARMAVLINK_Error.h>
#include "ARMAVLINK_ListUtils.h"

/**
 * @brief ARMavlink file generator structure allows to manage the process of creating Mavlink files
 */
struct ARMAVLINK_FileGenerator_t
{
    waypoint_list_t *waypointList;
};

/**
 * @brief Set again all the seq params of the waypoints starting at the given index of the list
 * @param list : the list to iterate in
 * @param[in] startIndex : the starting index
 * @return ARMAVLINK_OK if operation went well, the error description otherwise
 */
eARMAVLINK_ERROR ARMAVLINK_FileGenerator_ResetSequences(waypoint_list_t *list, int startIndex);

#endif
