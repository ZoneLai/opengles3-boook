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
     , _vboBuffers{0}
{
}

OpenGLRender::~OpenGLRender() {
    glDeleteBuffers(3, _vboBuffers);
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
        // 创建vbo对象
        glGenBuffers(3, _vboBuffers);
        // 绑定顶点
        glBindBuffer(GL_ARRAY_BUFFER, _vboBuffers[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_mVerticesData), _mVerticesData, GL_STATIC_DRAW);
        // 绑定颜色
        glBindBuffer(GL_ARRAY_BUFFER, _vboBuffers[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_mColorData), _mColorData, GL_STATIC_DRAW);
        // 绑定索引
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboBuffers[2]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indicesData), _indicesData, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
    // 设置视口大小
    glViewport(0, 0, _widgetWidth, _widgetHeight);
    // 清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    // 启用着色器
    glUseProgram(_sProgramPlay);
    // 设置mvp
    glUniformMatrix4fv(_mvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(_mvpMatrix));
    // 顶点
    glBindBuffer(GL_ARRAY_BUFFER, _vboBuffers[0]);
    glVertexAttribPointer(
        0,
        4,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(GL_FLOAT),
        (GLvoid*)0
    );
    glEnableVertexAttribArray(0);
    // 颜色
    glBindBuffer(GL_ARRAY_BUFFER, _vboBuffers[1]);
    glVertexAttribPointer(
        1,
        4,
        GL_FLOAT,
        GL_FALSE,
        4 * sizeof(GL_FLOAT),
        (GLvoid*)0
    );
    glEnableVertexAttribArray(1);
    // 索引
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboBuffers[2]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    // 关闭
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

GLint OpenGLRender::getTextureId() {
    return 0;
}