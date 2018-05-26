#pragma once
#include <GLES3/gl3.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include "Singleton.h"
#include "JniHelper.h"
class OpenGLRender : public Singleton<OpenGLRender> {
public:
    OpenGLRender();
    ~OpenGLRender();
    void                        onCreate();
    void                        onResume();
    void                        onPause();
    void                        onStop();
    void                        onDestroy();
    void                        initGL();
    void                        onSurfaceChanged(int widgetWidth, int widgetHeight);
    void                        drawFrame();
    GLint                       getTextureId();

private:
    GLuint                      _sProgramPlay;
    int                         _widgetWidth;
    int                         _widgetHeight;
    const GLfloat               _mVerticesData[9] = {
         0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

};