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
     , _vboBuffer(0)
     , _vaoBuffer(0)
{
}

OpenGLRender::~OpenGLRender() {
    glDeleteBuffers(1, &_vboBuffer);
    glDeleteVertexArrays(1, &_vaoBuffer);
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
        // 1.创建vao对象
        glGenVertexArrays(1, &_vaoBuffer);
        glBindVertexArray(_vaoBuffer);
        // 2.创建vbo对象、绑定顶点
        glGenBuffers(1, &_vboBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vboBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_mVerticesData), _mVerticesData, GL_STATIC_DRAW);
        // 顶点
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(GL_FLOAT),
            (GLvoid*)0
        );
        glEnableVertexAttribArray(0);
        // 颜色
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(GL_FLOAT),
            (GLvoid*)(3 * sizeof(GL_FLOAT))
        );
        glEnableVertexAttribArray(1);
        // 颜色
        glVertexAttribPointer(
            2,
            2,
            GL_FLOAT,
            GL_FALSE,
            8 * sizeof(GL_FLOAT),
            (GLvoid*)(6 * sizeof(GL_FLOAT))
        );
        glEnableVertexAttribArray(2);
        // 解除绑定
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);
    } else {
        LOGE("CompileShader Error=================");
    }
}

void OpenGLRender::onSurfaceChanged(int widgetWidth, int widgetHeight) {
    _widgetWidth        = widgetWidth;
    _widgetHeight       = widgetHeight;
    _modelMatrix        = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    _viewMatrix         = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _projectionMatrix   = glm::ortho(-1.0f, 1.0f, -(float) _widgetHeight / _widgetWidth, (float) _widgetHeight / _widgetWidth, 5.0f, 7.0f);
    _mvpMatrix		    = _projectionMatrix * _viewMatrix * _modelMatrix;
}

void OpenGLRender::drawFrame() {
    glBindVertexArray(_vaoBuffer);
    // 设置视口大小
    glViewport(0, 0, _widgetWidth, _widgetHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    // 启用着色器
    glUseProgram(_sProgramPlay);
    // 设置mvp
    glUniformMatrix4fv(_mvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(_mvpMatrix));

    glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
    glUseProgram(0);
}

void OpenGLRender::updateAngle(const float angle, const float xMove, const float yMove, const float zMove) {
    _modelMatrix        = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
    _viewMatrix         = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _viewMatrix         = glm::rotate(_viewMatrix, glm::radians(angle), glm::vec3(xMove, yMove, zMove));
    _projectionMatrix   = glm::ortho(-1.0f, 1.0f, -(float) _widgetHeight / _widgetWidth, (float) _widgetHeight / _widgetWidth, 5.0f, 7.0f);
    _mvpMatrix		    = _projectionMatrix * _viewMatrix * _modelMatrix;
}

GLint OpenGLRender::getTextureId() {
    return 0;
}