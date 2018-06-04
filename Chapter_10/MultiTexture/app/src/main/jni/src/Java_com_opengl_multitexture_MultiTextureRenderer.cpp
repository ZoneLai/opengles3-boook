#include "OpenGLRender.h"
#ifndef _Included_com_opengl_triangle_TriangleRenderer
#define _Included_com_opengl_triangle_TriangleRenderer
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeOnCreate(JNIEnv *env, jclass thiz) {
    if (OpenGLRender::getSingletonPtr() == nullptr) {
        new OpenGLRender();
    }
    OpenGLRender::getSingleton().onCreate();
}

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeInitGL(JNIEnv *env, jclass thiz, jobject assetManager, jstring jFileName, jstring jFileName2) {
    AAssetManager* mgr      = AAssetManager_fromJava(env, assetManager);
    const char* filePath    = env->GetStringUTFChars(jFileName, JNI_FALSE);
    const char* filePath2   = env->GetStringUTFChars(jFileName2, JNI_FALSE);
    OpenGLRender::getSingleton().initGL(mgr, filePath, filePath2);
    env->ReleaseStringUTFChars(jFileName, filePath);
    env->ReleaseStringUTFChars(jFileName2, filePath2);
}

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeOnResume(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onResume();
}

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeOnPause(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onPause();
}

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeOnStop(JNIEnv *env, jclass thiz) {
	OpenGLRender::getSingleton().onStop();
}

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeOnDestroy(JNIEnv *env, jclass thiz) {
    OpenGLRender::getSingleton().onDestroy();
}

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeDrawFrame(JNIEnv *env, jclass thiz) {
	OpenGLRender::getSingleton().drawFrame();
}

JNIEXPORT void JNICALL Java_com_opengl_multitexture_MultiTextureRenderer_nativeOnSurfaceChanged(JNIEnv *env, jclass thiz, jint widgetWidth, jint widgetHeight) {
	OpenGLRender::getSingleton().onSurfaceChanged(widgetWidth, widgetHeight);
}

#ifdef __cplusplus
}
#endif
#endif
