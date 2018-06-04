#include "OpenGLRender.h"
#include "Common.h"
#include "GLUtil.h"
#include "shader/triangle.frag"
#include "shader/triangle.vert"
#include "PngLoader.h"

template<> OpenGLRender* Singleton<OpenGLRender>::msSingleton = nullptr;
OpenGLRender::OpenGLRender()
     : _sProgramPlay(0)
     , _mvpMatrixLoc(0)
     , _sampler2DLoc(0)
     , _lightSampler2DLoc(0)
     , _mixValueLoc(0)
     , _widgetWidth(0)
     , _widgetHeight(0)
     , _photoWidth(0)
     , _photoHeight(0)
     , _mvpMatrix(glm::mat4(1.0f))
     , _modelMatrix(glm::mat4(1.0f))
     , _viewMatrix(glm::mat4(1.0f))
     , _projectionMatrix(glm::mat4(1.0f))
     , _vboBuffer(0)
     , _vaoBuffer(0)
     , _textures{0}
     , _textureData(nullptr)
{
}

OpenGLRender::~OpenGLRender() {
}

void OpenGLRender::onCreate() {
}

void OpenGLRender::onResume() {
}

void OpenGLRender::onPause() {
    glDeleteBuffers(1, &_vboBuffer);
    glDeleteVertexArrays(1, &_vaoBuffer);
    glDeleteTextures(2, _textures);
    glDeleteProgram(_sProgramPlay);
    if (_textureData) {
        delete[] _textureData;
        _textureData = nullptr;
    }
}

void OpenGLRender::onStop() {
}

void OpenGLRender::onDestroy() {
}

void OpenGLRender::initGL(AAssetManager* mgr, const char* fileName, const char* fileName2) {
    if (CompileShaderProgram(triangle_vert, triangle_frag, &_sProgramPlay)) {
        _mvpMatrixLoc       = glGetUniformLocation(_sProgramPlay, "u_mvpMatrix");
        _sampler2DLoc       = glGetUniformLocation(_sProgramPlay, "s_texture");
        _lightSampler2DLoc	= glGetUniformLocation(_sProgramPlay, "s_textureLight");
        _mixValueLoc		= glGetUniformLocation(_sProgramPlay, "u_mixValue");
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
            5 * sizeof(GL_FLOAT),
            (GLvoid*)0
        );
        glEnableVertexAttribArray(0);
        // 纹理坐标
        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(GL_FLOAT),
            (GLvoid*)(3 * sizeof(GL_FLOAT))
        );
        glEnableVertexAttribArray(1);
        // 解除绑定
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
        // 加载纹理数据, 注：还可以获取图片为RGB RGBA格式，先写死，回掉获取_hasAlpha为true\false判断
        _textureData = PngLoader::loadPngData(mgr, fileName, &_photoWidth, &_photoHeight);
        // 创建纹理
        glGenTextures(2, _textures);
        glBindTexture(GL_TEXTURE_2D, _textures[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _photoWidth, _photoHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, _textureData);
        if (_textureData) {
            delete[] _textureData;
            _textureData = nullptr;
        }
        _textureData = PngLoader::loadPngData(mgr, fileName2, &_photoWidth, &_photoHeight);
        glBindTexture(GL_TEXTURE_2D, _textures[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _photoWidth, _photoHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, _textureData);
        glBindTexture(GL_TEXTURE_2D, 0);
        if (_textureData) {
            delete[] _textureData;
            _textureData = nullptr;
        }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        LOGE("CompileShader Error=================");
    }
}

void OpenGLRender::onSurfaceChanged(int widgetWidth, int widgetHeight) {
    _widgetWidth        = widgetWidth;
    _widgetHeight       = widgetHeight;
    _modelMatrix        = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
    _viewMatrix         = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _projectionMatrix   = glm::ortho(-1.0f, 1.0f, -(float) _widgetHeight / _widgetWidth, (float) _widgetHeight / _widgetWidth, 5.0f, 7.0f);
    _mvpMatrix		    = _projectionMatrix * _viewMatrix * _modelMatrix;
}

void OpenGLRender::drawFrame() {
    LOGE("==============================");
    glBindVertexArray(_vaoBuffer);
    // 设置视口大小
    glViewport(0, 0, _widgetWidth, _widgetHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // 清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    // 启用着色器
    glUseProgram(_sProgramPlay);
    // 设置mvp
    glUniformMatrix4fv(_mvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(_mvpMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textures[0]);
    glUniform1i(_sampler2DLoc, 0);      // 设置纹理单元为0号

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _textures[1]);
    glUniform1i(_lightSampler2DLoc, 1); // 设置纹理单元为1号

    glUniform1f(_mixValueLoc, 0.7);

    glDrawArrays(GL_TRIANGLES, 0, 6);   // 顶点个数为6

	glBindVertexArray(0);
    glUseProgram(0);
}

GLint OpenGLRender::getTextureId() {
    return 0;
}