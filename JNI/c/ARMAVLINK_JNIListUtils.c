/*
    Copyright (C) 2014 Parrot SA

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the 
      distribution.
    * Neither the name of Parrot nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written
      permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
    OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
    OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/
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

#define ULOG_TAG armavlink_jni_listutils
#include <ulog.h>
ULOG_DECLARE_TAG(armavlink_jni_listutils);

#include <libARMavlink/ARMAVLINK_ListUtils.h>


/*****************************************
 *
 *             private header:
 *
 *****************************************/


/*****************************************
 *
 *             implementation :
 *
 *****************************************/

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
