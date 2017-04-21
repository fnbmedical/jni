LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)  
LOCAL_MODULE := ecgl    
LOCAL_SRC_FILES := ecgl/libecgl12.so       
include $(PREBUILT_SHARED_LIBRARY) 


include $(CLEAR_VARS)

LOCAL_MODULE    := main
LOCAL_SRC_FILES := main.c
LOCAL_LDLIBS    := -llog
    
LOCAL_STATIC_LIBRARIES := ecgl

include $(BUILD_SHARED_LIBRARY)
