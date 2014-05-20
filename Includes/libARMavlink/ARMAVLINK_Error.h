/**
 * @file ARMAVLINK_Error.h
 * @brief libARMavlink errors known.
 * @date 11/13/2013
 * @author frederic.dhaeyer@parrot.com
 */

#ifndef _ARMAVLINK_ERROR_H_
#define _ARMAVLINK_ERROR_H_

/**
 * @brief libARMavlink errors known.
 */
typedef enum
{
    ARMAVLINK_OK = 0,                                            /**< No error */
    
    ARMAVLINK_ERROR = -1000,                                     /**< Unknown generic error */
    ARMAVLINK_ERROR_ALLOC,                                       /**< Memory allocation error */
    ARMAVLINK_ERROR_BAD_PARAMETER,                               /**< Bad parameters */
    
    ARMAVLINK_ERROR_MANAGER = -2000,                             /**< Unknown ARMAVLINK_Manager error */
    
    ARMAVLINK_ERROR_FILE_GENERATOR = -3000,                      /**< Unknown ARMAVLINK_FileGenerator error */
    
    ARMAVLINK_ERROR_LIST_UTILS = -4000,                          /**< Unknown ARMAVLINK_ListUtils error */
    
    ARMAVLINK_ERROR_WAYPOINT_UTILS = -5000,                      /**< Unknown ARMAVLINK_WaypointUtils error */
    ARMAVLINK_ERROR_WAYPOINT_UTILS_NOT_LINKED_COMMAND,           /**< Command not linked with Mavlink commands */
    
    ARMAVLINK_ERROR_FILE_PARSER = -6000,                         /**< Unknown ARMAVLINK_FileParser error */
    ARMAVLINK_ERROR_FILE_PARSER_FILE_NOT_FOUND,                  /**< File to parse not found */
    ARMAVLINK_ERROR_FILE_PARSER_WORD_NOT_EXPTECTED,              /**< A word was not expected during parsing */

} eARMAVLINK_ERROR;

/**
 * @brief Gets the error string associated with an eARMAVLINK_ERROR
 * @param error The error to describe
 * @return A static string describing the error
 *
 * @note User should NEVER try to modify a returned string
 */
char* ARMAVLINK_Error_ToString (eARMAVLINK_ERROR error);

#endif // _ARMAVLINK_ERROR_H_
