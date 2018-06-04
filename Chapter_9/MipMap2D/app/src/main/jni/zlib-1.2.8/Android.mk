# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH	:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := libz

LOCAL_CFLAGS    := -Werror

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/ \

LOCAL_SRC_FILES := \
    $(LOCAL_PATH)/ \
    $(LOCAL_PATH)/adler32.c	\
    $(LOCAL_PATH)/compress.c \
    $(LOCAL_PATH)/crc32.c \
    $(LOCAL_PATH)/deflate.c	\
    $(LOCAL_PATH)/gzclose.c	\
    $(LOCAL_PATH)/gzlib.c \
    $(LOCAL_PATH)/gzread.c \
    $(LOCAL_PATH)/gzwrite.c	\
    $(LOCAL_PATH)/infback.c	\
    $(LOCAL_PATH)/inffast.c	\
    $(LOCAL_PATH)/inflate.c	\
    $(LOCAL_PATH)/inftrees.c \
    $(LOCAL_PATH)/trees.c \
    $(LOCAL_PATH)/uncompr.c	\
    $(LOCAL_PATH)/zutil.c

include $(BUILD_STATIC_LIBRARY)