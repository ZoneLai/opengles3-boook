#include "OpenGLRender.h"
#ifndef _Included_com_opengl_triangle_TriangleRenderer
#define _Included_com_opengl_triangle_TriangleRenderer
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeOnCreate(JNIEnv *env, jclass thiz) {
    if (OpenGLRender::getSingletonPtr() == nullptr) {
        new OpenGLRender();
    }
    OpenGLRender::getSingleton().onCreate();
}

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeInitGL(JNIEnv *env, jclass thiz, jobject assetManager, jstring jFileName) {
    AAssetManager* mgr      = AAssetManager_fromJava(env, assetManager);
    const char* filePath    = env->GetStringUTFChars(jFileName, JNI_FALSE);
    OpenGLRender::getSingleton().initGL(mgr, filePath);
    env->ReleaseStringUTFChars(jFileName, filePath);
}

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeOnResume(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onResume();
}

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeOnPause(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onPause();
}

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeOnStop(JNIEnv *env, jclass thiz) {
	OpenGLRender::getSingleton().onStop();
}

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeOnDestroy(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onDestroy();
}

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeDrawFrame(JNIEnv *env, jclass thiz) {
	OpenGLRender::getSingleton().drawFrame();
}

JNIEXPORT void JNICALL Java_com_opengl_mipmap2d_MipMap2DRenderer_nativeOnSurfaceChanged(JNIEnv *env, jclass thiz, jint widgetWidth, jint widgetHeight) {
	OpenGLRender::getSingleton().onSurfaceChanged(widgetWidth, widgetHeight);
}

#ifdef __cplusplus
}
#endif
#endif
