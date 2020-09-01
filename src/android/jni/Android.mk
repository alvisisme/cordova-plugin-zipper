LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := prebuilt-libzip
LOCAL_SRC_FILES := thirdparty/libzip/lib/$(TARGET_ARCH_ABI)/libzip.so
LOCAL_EXPORT_C_INCLUDES := thirdparty/libzip/include
LOCAL_EXPORT_LDFLAGS := -lz
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := zipper_jni
LOCAL_C_INCLUDES := $(LOCAL_PATH)/src 
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/src/zipper.cpp \
	$(LOCAL_PATH)/src/zipper_jni.cpp
LOCAL_CPPFLAGS := -fpermissive -std=c++11
LOCAL_LDFLAGS := -lstdc++ -llog
LOCAL_SHARED_LIBRARIES := prebuilt-libzip
include $(BUILD_SHARED_LIBRARY)