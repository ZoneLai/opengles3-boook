#include "OpenGLRender.h"
#include "Common.h"
#include "GLUtil.h"
#include "shader/triangle.frag"
#include "shader/triangle.vert"

template<> OpenGLRender* Singleton<OpenGLRender>::msSingleton = nullptr;
OpenGLRender::OpenGLRender()
    : _sProgramPlay(0)
    , _widgetWidth(0)
    , _widgetHeight(0)
{
}

OpenGLRender::~OpenGLRender() {
    glDeleteProgram(_sProgramPlay);
}

void OpenGLRender::onCreate() {
}

void OpenGLRender::onResume() {
}

void OpenGLRender::onPause() {
}

void OpenGLRender::onStop() {
}

void OpenGLRender::onDestroy() {
}

void OpenGLRender::initGL() {
    if (CompileShaderProgram(triangle_vert, triangle_frag, &_sProgramPlay)) {
        //glBindAttribLocation(_sProgramPlay, 0, "v_position");
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    } else {
      LOGE("CompileShader Error=================");
    }
}

void OpenGLRender::onSurfaceChanged(int widgetWidth, int widgetHeight) {
    _widgetWidth    = widgetWidth;
    _widgetHeight   = widgetHeight;
}

void OpenGLRender::drawFrame() {
    LOGE("==============================");
    // Set the viewport
    glViewport(0, 0, _widgetWidth, _widgetHeight);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(_sProgramPlay);

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, _mVerticesData);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLint OpenGLRender::getTextureId() {
    return 0;
}