#include "OpenGLRender.h"
#ifndef _Included_com_opengl_triangle_TriangleRenderer
#define _Included_com_opengl_triangle_TriangleRenderer
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeOnCreate(JNIEnv *env, jclass thiz) {
    if (OpenGLRender::getSingletonPtr() == nullptr) {
        new OpenGLRender();
    }
    OpenGLRender::getSingleton().onCreate();
}

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeInitGL(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().initGL();
}

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeOnResume(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onResume();
}

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeOnPause(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onPause();
}

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeOnStop(JNIEnv *env, jclass thiz) {
	OpenGLRender::getSingleton().onStop();
}

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeOnDestroy(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onDestroy();
}

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeDrawFrame(JNIEnv *env, jclass thiz) {
	OpenGLRender::getSingleton().drawFrame();
}

JNIEXPORT void JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeOnSurfaceChanged(JNIEnv *env, jclass thiz, jint widgetWidth, jint widgetHeight) {
	OpenGLRender::getSingleton().onSurfaceChanged(widgetWidth, widgetHeight);
}

JNIEXPORT jint JNICALL Java_com_opengl_triangle_TriangleRenderer_nativeGetTextureId(JNIEnv *env, jclass thiz) {
	return OpenGLRender::getSingleton().getTextureId();
}

#ifdef __cplusplus
}
#endif
#endif
