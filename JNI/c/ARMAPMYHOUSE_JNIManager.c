/**
 * @file ARMAVLINK_JNIManager.c
 * @brief JNI between the ARMAVLINK_Manager.h and ARMAVLINK_Manager.java
 * @date 11/13/2013
 * @author frederic.dhaeyer@parrot.com
 */

/*****************************************
 *
 *             include file :
 *
 *****************************************/

#include <jni.h>
#include <stdlib.h>

#include <libARSAL/ARSAL_Print.h>
#include <libARMavlink/ARMAVLINK_Error.h>
#include <libARMavlink/ARMAVLINK_Manager.h>

/*****************************************
 *
 *             private header:
 *
 *****************************************/

#define ARMAVLINK_JNIMANAGER_TAG "ARMAVLINK_JNIManager" /** tag used by the print of the file */

/*****************************************
 *
 *             implementation :
 *
 *****************************************/

static JavaVM* gARMAVLINK_JNIManager_VM = NULL; /** reference to the java virtual machine */
static jmethodID nativeDataSetUsed_id = 0;

/**
 * @brief save the reference to the java virtual machine
 * @note this function is automatically call on the JNI startup
 * @param[in] VM reference to the java virtual machine
 * @param[in] reserved data reserved
 * @return JNI version
 */
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *VM, void *reserved)
{
    ARSAL_PRINT(ARSAL_PRINT_DEBUG, ARMAVLINK_JNIMANAGER_TAG, "Library has been loaded");

    /** Saving the reference to the java virtual machine */
    gARMAVLINK_JNIManager_VM = VM;

    /** Return the JNI version */
    return JNI_VERSION_1_6;
}

/**
 * @brief Create a new manager
 * @warning This function allocate memory
 * @param env reference to the java environment
 * @param obj reference to the object calling this function
 * @param[in] type type of decoder
 * @return Pointer on the ARMAVLINK_Manager_t.
 * @see Java_com_parrot_arsdk_armavlink_ARMavlinkManager_nativeDelete()
 *
 */
JNIEXPORT jlong JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkManager_nativeNew(JNIEnv *env, jobject obj, jint type)
{
    /** -- Create a new manager -- */

    /** local declarations */
    ARMAVLINK_Manager_t *manager = NULL;
    eARMAVLINK_ERROR error = ARMAVLINK_OK;

    /** create the manager */
    manager = ARMAVLINK_Manager_New(type, &error);

    /** print error */
    if(error != ARMAVLINK_OK)
    {
        ARSAL_PRINT(ARSAL_PRINT_ERROR, ARMAVLINK_JNIMANAGER_TAG, "error: %s", ARMAVLINK_Error_ToString (error));
    }

    return managerPtr;
}

/**
 * @brief Delete the Manager
 * @warning This function free memory
 * @param env reference to the java environment
 * @param obj reference to the object calling this function
 * @param jManagerPtr adress of the ARMAVLINK_Manager_t
 * @see Java_com_parrot_arsdk_armavlink_ARMavlinkManager_nativeNew()
 */
JNIEXPORT void JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkManager_nativeDelete(JNIEnv *env, jobject obj, jlong jManagerPtr)
{
    /** -- Delete the Manager -- */

    ARMAVLINK_Manager_t *managerPtr = (ARMAVLINK_Manager_t*) (intptr_t) jManagerPtr;
    ARMAVLINK_Manager_Delete(&managerPtr);
}
