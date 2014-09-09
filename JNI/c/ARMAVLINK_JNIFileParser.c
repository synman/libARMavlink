/**
 * @file ARMAVLINK_JNIFileGenerator.c
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
#include <libARMavlink/ARMAVLINK_Error.h>
#include <libARMavlink/ARMAVLINK_FileParser.h>

/*****************************************
 *
 *             private header:
 *
 *****************************************/

#define ARMAVLINK_JNIMAVLINK_TAG "ARMAVLINK_JNIFileParser" /** tag used by the print of the file */

JNIEXPORT jlong JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkFileParser_nativeNew (JNIEnv *env, jobject obj)
{

    ARMAVLINK_FileParser_t *nativeFileParser = NULL;
    eARMAVLINK_ERROR result = ARMAVLINK_OK;

    nativeFileParser = ARMAVLINK_FileParser_New(&result);
    int error = Load_ARMavlink_Java_Exception(env);

    if (error != JNI_OK)
    {
        result = ARMAVLINK_ERROR;
    }
    if (result != ARMAVLINK_OK)
    {
        ARSAL_PRINT (ARSAL_PRINT_DEBUG, ARMAVLINK_JNIMAVLINK_TAG, "error: %d occurred", result);
        Throw_Mavlink_Exception(env, result);
    }

    return (long)nativeFileParser;
}

JNIEXPORT void JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkFileParser_nativeDelete (JNIEnv *env, jobject obj, jlong fileParserPtr)
{
	ARMAVLINK_FileParser_t *nativeFileParser = (ARMAVLINK_FileParser_t*) (intptr_t) fileParserPtr;

    ARMAVLINK_FileParser_Delete (&nativeFileParser);

    DeLoad_ARMavlink_Java_Exception(env);
}

JNIEXPORT void JNICALL
Java_com_parrot_arsdk_armavlink_ARMavlinkFileParser_nativeParse (JNIEnv *env, jobject obj, jlong fileParserPtr, jstring path, jlong missionListPtr)
{
	ARMAVLINK_FileParser_t *nativeFileParser = (ARMAVLINK_FileParser_t*) (intptr_t) fileParserPtr;
	mission_item_list_t *nativeMissionList = (mission_item_list_t*) (intptr_t) missionListPtr;
    const char *filePath = (*env)->GetStringUTFChars(env, path, 0);

	eARMAVLINK_ERROR result = ARMAVLINK_FileParser_Parse(nativeFileParser, filePath, nativeMissionList);

    if (result != ARMAVLINK_OK)
    {
        ARSAL_PRINT (ARSAL_PRINT_DEBUG, ARMAVLINK_JNIMAVLINK_TAG, "error: %d occurred", result);
        Throw_Mavlink_Exception(env, result);
    }
}
