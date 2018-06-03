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
    void                        updateAngle(const float angle, const float xMove, const float yMove, const float zMove);
    GLint                       getTextureId();

private:
    GLuint                      _sProgramPlay;
    GLint						_mvpMatrixLoc;
    int                         _widgetWidth;
    int                         _widgetHeight;
    const GLfloat               _mVerticesData[36 * 8] = {
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// A
         0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// B
         0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// C
         0.5f,  0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// C
        -0.5f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// D
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// A

        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// E
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // H
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// G
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// G
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// F
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// E

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// D
        -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // H
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,	// E
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,	// E
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// A
        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	// D

        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// F
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// G
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,   // C
        0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,   // C
        0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,	// B
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// F

         0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// G
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // H
        -0.5f, 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	// D
        -0.5f, 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	// D
         0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,	// C
         0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	// G

        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// A
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,	// E
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// F
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// F
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	// B
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,	// A
    };
    glm::mat4                   _mvpMatrix;
    glm::mat4                   _modelMatrix;
    glm::mat4                   _viewMatrix;
    glm::mat4                   _projectionMatrix;
    GLuint                      _vboBuffer;
    GLuint                      _vaoBuffer;
};