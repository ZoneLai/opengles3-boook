#include "OpenGLRender.h"
#include "Common.h"
#include "GLUtil.h"
#include "shader/triangle.frag"
#include "shader/triangle.vert"
#include "PngLoader.h"
#include <ctime>
template<> OpenGLRender* Singleton<OpenGLRender>::msSingleton = nullptr;
OpenGLRender::OpenGLRender()
     : _sProgramPlay(0)
     , _mvpMatrixLoc(0)
     , _sampler2DLoc(0)
     , _uTimeLoc(0)
     , _uCenterPositionLoc(0)
     , _uColorLoc(0)
     , _widgetWidth(0)
     , _widgetHeight(0)
     , _photoWidth(0)
     , _photoHeight(0)
     , _mParticleData{0}
     , _mvpMatrix(glm::mat4(1.0f))
     , _modelMatrix(glm::mat4(1.0f))
     , _viewMatrix(glm::mat4(1.0f))
     , _projectionMatrix(glm::mat4(1.0f))
     , _vboBuffer(0)
     , _vaoBuffer(0)
     , _textures{0}
     , _textureData(nullptr)
     , _lastTime(0)
     , _mTime(0)
     , _centerPos{0}
     , _fragColor{0}
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
    glDeleteTextures(1, _textures);
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

void OpenGLRender::randomPosition() {
    std::uniform_int_distribution<unsigned> u(1, 10000);
    std::default_random_engine e(time(nullptr));
    for (auto i = 0; i < NUM_PARTICLES * PARTICLE_SIZE; i += PARTICLE_SIZE) {
        // Lifetime of particle
        _mParticleData[i + 0] = u(e) / 10000.0f;

        // End position of particle
        _mParticleData[i + 1] = (u(e) / 5000.0f) - 1.0f;
        _mParticleData[i + 2] = (u(e) / 5000.0f) - 1.0f;
        _mParticleData[i + 3] = (u(e) / 5000.0f) - 1.0f;

        // Start position of particle
        _mParticleData[i + 4] = (u(e) / 40000.0f) - 0.125f;
        _mParticleData[i + 5] = (u(e) / 40000.0f) - 0.125f;
        _mParticleData[i + 6] = (u(e) / 40000.0f) - 0.125f;
    }
}

void OpenGLRender::initGL(AAssetManager* mgr, const char* fileName) {
    if (CompileShaderProgram(triangle_vert, triangle_frag, &_sProgramPlay)) {
        _mvpMatrixLoc       = glGetUniformLocation(_sProgramPlay, "u_mvpMatrix");
        _uTimeLoc           = glGetUniformLocation(_sProgramPlay, "u_time");
        _uCenterPositionLoc = glGetUniformLocation(_sProgramPlay, "u_centerPosition");
        _uColorLoc          = glGetUniformLocation(_sProgramPlay, "u_color");
        _sampler2DLoc       = glGetUniformLocation(_sProgramPlay, "s_texture");
        // 随机数生成顶点数据
        randomPosition();
        // 1.创建vao对象
        glGenVertexArrays(1, &_vaoBuffer);
        glBindVertexArray(_vaoBuffer);
        // 2.创建vbo对象、绑定顶点
        glGenBuffers(1, &_vboBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vboBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(_mParticleData), _mParticleData, GL_STATIC_DRAW);
        // 生命周期
        glVertexAttribPointer(
            0,
            1,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GL_FLOAT),
            (GLvoid*)0
        );
        glEnableVertexAttribArray(0);
        // 开始位置
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GL_FLOAT),
            (GLvoid*)(1 * sizeof(GL_FLOAT))
        );
        glEnableVertexAttribArray(1);
        // 结束位置
        glVertexAttribPointer(
            2,
            3,
            GL_FLOAT,
            GL_FALSE,
            7 * sizeof(GL_FLOAT),
            (GLvoid*)(4 * sizeof(GL_FLOAT))
        );
        glEnableVertexAttribArray(2);
        // 解除绑定
        glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
        // 加载纹理数据, 注：还可以获取图片为RGB RGBA格式，先写死，回掉获取_hasAlpha为true\false判断
        _textureData = PngLoader::loadPngData(mgr, fileName, &_photoWidth, &_photoHeight);
        // 创建纹理
        glGenTextures(1, _textures);
        glBindTexture(GL_TEXTURE_2D, _textures[0]);
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
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
    // 设置视口大小
    glViewport(0, 0, _widgetWidth, _widgetHeight);
}

int64_t OpenGLRender::getCurrentTime() {
    time_t timesec;
    struct tm *p;
    time(&timesec);
    p = localtime(&timesec);
    return p->tm_min * 60 * 1000 + p->tm_sec * 1000;
}

void OpenGLRender::upDateTimeAndColor() {
    if (_lastTime == 0) {
        _lastTime = getCurrentTime();
    }
    long curTime        = getCurrentTime();
    long elapsedTime    = curTime - _lastTime;
    float deltaTime     = elapsedTime / 1000.0f;
    _lastTime           = curTime;
    _mTime              += deltaTime;
    if (_mTime >= 1.0f) {
        _mTime = 0.0f;
        std::uniform_int_distribution<unsigned> u(1, 10000);
        std::default_random_engine e(time(nullptr));
        // Pick a new start location and color
        _centerPos[0] = (u(e) / 10000.0f) - 0.5f;
        _centerPos[1] = (u(e) / 10000.0f) - 0.5f;
        _centerPos[2] = (u(e) / 10000.0f) - 0.5f;
        glUniform3fv(_uCenterPositionLoc, 1, _centerPos);
        // Random color
        _fragColor[0] = (u(e) / 20000.0f) + 0.5f;
        _fragColor[1] = (u(e) / 20000.0f) + 0.5f;
        _fragColor[2] = (u(e) / 20000.0f) + 0.5f;
        _fragColor[3] = 0.5f;
        glUniform4fv(_uColorLoc, 1, _fragColor);

    }
    // Load uniform time variable
    glUniform1f(_uTimeLoc, _mTime);
}

void OpenGLRender::drawFrame() {
    glBindVertexArray(_vaoBuffer);
    // 清除颜色缓冲区
    glClear(GL_COLOR_BUFFER_BIT);
    // 启用着色器
    glUseProgram(_sProgramPlay);
    // 设置mvp
    glUniformMatrix4fv(_mvpMatrixLoc, 1, GL_FALSE, glm::value_ptr(_mvpMatrix));
    // 更新
    upDateTimeAndColor();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textures[0]);
    glUniform1i(_sampler2DLoc, 0);               // 设置纹理单元为0号

    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);   // 顶点个数为NUM_PARTICLES

	glBindVertexArray(0);
    glUseProgram(0);
}

GLint OpenGLRender::getTextureId() {
    return 0;
}