/*
 * GENERATED FILE
 *  Do not modify this file, it will be erased during the next configure run
 */

/**
 * @file ARMAVLINK_Error.c
 * @brief ToString function for eARMAVLINK_ERROR enum
 */

#include <libARMavlink/ARMAVLINK_Error.h>

char* ARMAVLINK_Error_ToString (eARMAVLINK_ERROR error)
{
    switch (error)
    {
    case ARMAVLINK_OK:
        return "No error";
        break;
    case ARMAVLINK_ERROR:
        return "Unknown generic error";
        break;
    case ARMAVLINK_ERROR_ALLOC:
        return "Memory allocation error";
        break;
    case ARMAVLINK_ERROR_BAD_PARAMETER:
        return "Bad parameters";
        break;
    case ARMAVLINK_ERROR_MANAGER:
        return "Unknown ARMAVLINK_Manager error";
        break;
    default:
        return "Unknown value";
        break;
    }
    return "Unknown value";
}
