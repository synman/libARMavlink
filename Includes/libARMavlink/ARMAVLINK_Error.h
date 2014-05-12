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
