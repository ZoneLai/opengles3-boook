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
    // 设置视口大小
    glViewport(0, 0, _widgetWidth, _widgetHeight);
    // 清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    // 启用着色器
    glUseProgram(_sProgramPlay);
    // 设置颜色属性值，r、g、b、a
    glVertexAttrib4f(0, 1.0f, 0.0f, 0.0f, 1.0f);
    // 加载顶点数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, _mVerticesData);
    // 启用
    glEnableVertexAttribArray(1);
    // 绘制三角形，3个顶点
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // 关闭
    glDisableVertexAttribArray(1);
    glUseProgram(0);
}

GLint OpenGLRender::getTextureId() {
    return 0;
}