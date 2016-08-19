LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

TARGET_PLATFORM := 17
LOCAL_MODULE    := NDKExample

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../include $(LOCAL_PATH)/../PH7

FILE_LIST += $(wildcard $(LOCAL_PATH)/../src/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += ../PH7/ph7.c

LOCAL_LDLIBS    := -llog -landroid #-lEGL -lGLESv2 -latomic
# LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

# $(call import-module,android/native_app_glue)
