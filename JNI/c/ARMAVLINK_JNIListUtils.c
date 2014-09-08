/**
 * @file ARMAVLINK_JNIListUtils.c
 * @brief 
 * @date 
 * @author 
 */

/*****************************************
 *
 *             include file :
 *
 *****************************************/

#include <jni.h>
#include <stdlib.h>

#include <libARSAL/ARSAL_Print.h>

#include <libARMavlink/ARMAVLINK_ListUtils.h>


/*****************************************
 *
 *             private header:
 *
 *****************************************/

#define ARMAVLINK_JNIMAVLINK_TAG "JNIMavlinkListUtils" /** tag used by the print of the file */

static JavaVM* gARMAVLINK_JNIMavlink_VM = NULL; /** reference to the java virtual machine */


/*****************************************
 *
 *             implementation :
 *
 *****************************************/

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
    ARSAL_PRINT(ARSAL_PRINT_DEBUG, ARMAVLINK_JNIMAVLINK_TAG, "Library has been loaded");

    /** Saving the reference to the java virtual machine */
    gARMAVLINK_JNIMavlink_VM = VM;

    /** Return the JNI version */
    return JNI_VERSION_1_6;
}

JNIEXPORT jlong JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkMissionItemList_nativeMissionItemListNew (JNIEnv *env, jclass class)
{
    return (long) ARMAVLINK_ListUtils_MissionItemListNew();
}

JNIEXPORT void JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkMissionItemList_nativeMissionItemListDelete(JNIEnv *env, jobject obj, jlong jListPtr)
{
    mission_item_list_t *list = (mission_item_list_t*) (intptr_t) jListPtr;
    ARMAVLINK_ListUtils_MissionItemListDelete(&list);
}

JNIEXPORT jint JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkMissionItemList_nativeMissionItemListGetSize(JNIEnv *env, jobject obj, jlong jListPtr)
{
    const mission_item_list_t *list = (const mission_item_list_t*) (intptr_t) jListPtr;
    return ARMAVLINK_ListUtils_MissionItemListGetSize(list);
}

JNIEXPORT jlong JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkMissionItemList_nativeMissionItemListGet(JNIEnv *env, jobject obj, jlong jListPtr, jint index)
{
    const mission_item_list_t *list = (const mission_item_list_t*) (intptr_t) jListPtr;
    const uint16_t mIndex = (const uint16_t) index;
    return (long) ARMAVLINK_ListUtils_MissionItemListGet(list, mIndex);
}
