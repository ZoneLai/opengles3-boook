#include "OpenGLRender.h"
#include "Common.h"
#include "GLUtil.h"
#include "shader/triangle.frag"
#include "shader/triangle.vert"

template<> OpenGLRender* Singleton<OpenGLRender>::msSingleton = nullptr;
OpenGLRender::OpenGLRender()
    : _sProgramPlay(0)
    , _mvpMatrixLoc(0)
    , _widgetWidth(0)
    , _widgetHeight(0)
    , _mvpMatrix(glm::mat4(1.0f))
    , _modelMatrix(glm::mat4(1.0f))
    , _viewMatrix(glm::mat4(1.0f))
    , _projectionMatrix(glm::mat4(1.0f))
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
        _mvpMatrixLoc = glGetUniformLocation(_sProgramPlay, "u_mvpMatrix");
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    } else {
      LOGE("CompileShader Error=================");
    }
}

void OpenGLRender::onSurfaceChanged(int widgetWidth, int widgetHeight) {
    _widgetWidth        = widgetWidth;
    _widgetHeight       = widgetHeight;
    _viewMatrix         = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _projectionMatrix   = glm::ortho(-1.0f, 1.0f, -(float) _widgetHeight / _widgetWidth, (float) _widgetHeight / _widgetWidth, 5.0f, 7.0f);
    _mvpMatrix		    = _projectionMatrix * _viewMatrix * _modelMatrix;
}

void OpenGLRender::drawFrame() {
    LOGE("==============================");
    // Set the viewport
    glViewport(0, 0, _widgetWidth, _widgetHeight);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the program object
    glUseProgram(_sProgramPlay);
    glUniformMatrix4fv(_mvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(_mvpMatrix));

    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, _mVerticesData);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);
}

GLint OpenGLRender::getTextureId() {
    return 0;
}