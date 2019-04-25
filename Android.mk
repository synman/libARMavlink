LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libarmavlink-jni

LOCAL_CFLAGS = -Wno-address-of-packed-member

LOCAL_SRC_FILES := \
	JNI/c/ARMAVLINK_JNIListUtils.c \
	JNI/c/ARMAVLINK_JNIFileParser.c \
	JNI/c/ARMAVLINK_JNIFileGenerator.c \
	JNI/c/ARMAVLINK_JNIMissionItemUtils.c

LOCAL_STATIC_LIBRARIES := \
	libARMavlink-static \
	libulog-static

include $(BUILD_SDKCORE_MODULE)
