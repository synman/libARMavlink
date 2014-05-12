/**
 * @file ARMAVLINK_Manager.h
 * @brief ARMavlink manager.
 * @date 11/13/2013
 * @author frederic.dhaeyer@parrot.com
 */

#ifndef _ARMAVLINK_MANAGER_H_
#define _ARMAVLINK_MANAGER_H_

#include <libARMavlink/ARMAVLINK_Error.h>

/**
 * @brief MapMyHouse manager structure allows to manage the MapMyHouse process
 */
typedef struct ARMAVLINK_Manager_t ARMAVLINK_Manager_t;

/**
 * @brief Create a new Manager
 * @warning This function allocate memory
 * @post ARMAVLINK_Manager_Delete() must be called to delete the MapMyHouse manager and free the memory allocated.
 * @param[out] error : pointer on the error output.
 * @return Pointer on the new Manager
 * @see ARMAVLINK_Manager_Delete()
 */
ARMAVLINK_Manager_t* ARMAVLINK_Manager_New(eARMAVLINK_ERROR *error);

/**
 * @brief Delete the Manager
 * @warning This function free memory
 * @param manager : address of the pointer on the Manager
 * @see ARMAVLINK_Manager_New()
 */
void ARMAVLINK_Manager_Delete(ARMAVLINK_Manager_t **manager);

#endif /* _ARMAVLINK_MANAGER_H_ */
