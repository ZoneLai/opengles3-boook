//========================================================
/**
*  @file  OpenGLRender.cpp
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
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GLES3/gl3.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "png.h"

class PngLoader {
private:
    PngLoader() {}
    ~PngLoader() {}

    static void getAssetStream(AAssetManager* mgr, const char* filePath, std::vector<char> &buffer);

    static void readFileCallback(png_structp png_ptr, png_bytep destination, png_size_t bytesToRead);

public:
    static GLuint* loadPngData(AAssetManager* mgr, const char* fileName, int* textureWidth, int* textureHeight);
};