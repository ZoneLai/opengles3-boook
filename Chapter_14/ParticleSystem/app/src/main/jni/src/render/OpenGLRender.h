//========================================================
/**
*  @file  OpenGLRender.h
*
*  项目描述：
*  文件描述:
*  适用平台：
*
*  作者：     赖忠安
*  电子邮件:  zhonganlai@gmail.com
*  创建日期： 20017-07-24
*  修改日期： 20017-07-25
*
*/
//========================================================
#pragma once
#include <GLES3/gl3.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include <random>
#include "Singleton.h"
#include "JniHelper.h"
#include "glm.hpp"
#include "ext.hpp"
#define NUM_PARTICLES               1000
#define PARTICLE_SIZE               7
class OpenGLRender : public Singleton<OpenGLRender> {
public:
    OpenGLRender();
    ~OpenGLRender();
    void                        onCreate();
    void                        onResume();
    void                        onPause();
    void                        onStop();
    void                        onDestroy();
    void                        initGL(AAssetManager* mgr, const char* fileName);
    void                        onSurfaceChanged(int widgetWidth, int widgetHeight);
    void                        drawFrame();
    GLint                       getTextureId();

private:
    void                        randomPosition();
    void                        upDateTimeAndColor();
    int64_t                     getCurrentTime();

private:
    GLuint                      _sProgramPlay;
    GLint						_mvpMatrixLoc;
    GLint                       _sampler2DLoc;
    GLint                       _uTimeLoc;
    GLint                       _uCenterPositionLoc;
    GLint                       _uColorLoc;
    int                         _widgetWidth;
    int                         _widgetHeight;
    int                         _photoWidth;
    int                         _photoHeight;
    GLfloat                     _mParticleData[NUM_PARTICLES * PARTICLE_SIZE];
    glm::mat4                   _mvpMatrix;
    glm::mat4                   _modelMatrix;
    glm::mat4                   _viewMatrix;
    glm::mat4                   _projectionMatrix;
    GLuint                      _vboBuffer;
    GLuint                      _vaoBuffer;
    GLuint                      _textures[1];
    GLuint*                     _textureData;
    long                        _lastTime;
    long                        _mTime;
    float                       _centerPos[3];
    float                       _fragColor[4];
};