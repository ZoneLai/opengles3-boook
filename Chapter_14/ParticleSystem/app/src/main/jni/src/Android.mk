LOCAL_PATH	:= $(call my-dir)
include $(CLEAR_VARS)

CFLAGS := -Werror

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/ \
        $(LOCAL_PATH)/../ \
        $(LOCAL_PATH)/base/ \
        $(LOCAL_PATH)/model/ \
        $(LOCAL_PATH)/render/ \
        $(LOCAL_PATH)/util/ \
        $(LOCAL_PATH)/../glm \
        $(LOCAL_PATH)/../glm/glm \
        $(LOCAL_PATH)/../glm/glm/detail \
        $(LOCAL_PATH)/../glm/glm/gtc \
        $(LOCAL_PATH)/../glm/glm/gtx

LOCAL_CFLAGS := $(LOCAL_C_INCLUDES:%=-I%)
LOCAL_CFLAGS += -DANDROID_NDK
LOCAL_CFLAGS += -DLOG_NDEBUG
LOCAL_CFLAGS += -DACCESS_RAW_DESCRIPTORS
LOCAL_CFLAGS += -DHAVE_CONFIG_H
LOCAL_CFLAGS += -fprefetch-loop-arrays -Wno-conversion-null
LOCAL_CFLAGS += -O3 -fstrict-aliasing -fprefetch-loop-arrays -O3 -ffast-math -Wno-conversion-null -Wno-write-strings -Wno-error=format-security

APP_CFLAG    := -O3 -ffast-math -Wno-conversion-null -Wno-write-strings -Wno-error=format-security

LOCAL_LDLIBS :=-lOpenSLES -L$(SYSROOT)/usr/lib -ljnigraphics -lEGL -lGLESv3 -llog -ldl -landroid -latomic

LOCAL_ARM_MODE := arm
LOCAL_STATIC_LIBRARIES += png1628

LOCAL_SRC_FILES := \
        ../glm/glm/detail/dummy.cpp \
        ../glm/glm/detail/glm.cpp \
        util/GLInfo.cpp \
        util/GLUtil.cpp \
        model/PngLoader.cpp \
        render/OpenGLRender.cpp \
        Common.cpp \
        Java_com_opengl_particlesystem_ParticleSystemRenderer.cpp


LOCAL_DISABLE_FORMAT_STRING_CHECKS := true
LOCAL_MODULE    := opengl-lib

include $(BUILD_SHARED_LIBRARY)