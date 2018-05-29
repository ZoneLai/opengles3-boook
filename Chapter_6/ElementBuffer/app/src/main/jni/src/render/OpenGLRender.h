#pragma once
#include <GLES3/gl3.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include "Singleton.h"
#include "JniHelper.h"
#include "glm.hpp"
#include "ext.hpp"
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
    GLint						_mvpMatrixLoc;
    int                         _widgetWidth;
    int                         _widgetHeight;
    const GLfloat               _mVerticesData[16] = {
        -0.5f,  0.0f, 0.0f, 1.0f,  // 0
         0.5f,  0.0f, 0.0f, 1.0f,  // 1
         0.0f,  0.5f, 0.0f, 1.0f,  // 2
         0.0f, -0.5f, 0.0f, 1.0f   // 3
    };
    const GLfloat               _mColorData[12] = {
        1.0f, 0.0f, 0.0f, 1.0f,   // c0
        0.0f, 1.0f, 0.0f, 1.0f,   // c1
        0.0f, 0.0f, 1.0f, 1.0f    // c2
    };
    const GLushort              _indicesData[6] = {
        0, 1, 2,  // 第一个三角形
        0, 3, 1   // 第二个三角形
    };
    glm::mat4                   _mvpMatrix;
    glm::mat4                   _modelMatrix;
    glm::mat4                   _viewMatrix;
    glm::mat4                   _projectionMatrix;
    GLuint                      _vboBuffers[3];
};