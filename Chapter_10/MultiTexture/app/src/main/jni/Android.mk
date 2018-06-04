#include $(call all-subdir-makefiles)
PROJ_PATH := $(call my-dir)
include $(CLEAR_VARS)
#include $(PROJ_PATH)/libpng-1.6.15/Android.mk
include $(PROJ_PATH)/lpng1628/projects/android/jni/Android.mk
include $(PROJ_PATH)/zlib-1.2.8/Android.mk
include $(PROJ_PATH)/src/Android.mk