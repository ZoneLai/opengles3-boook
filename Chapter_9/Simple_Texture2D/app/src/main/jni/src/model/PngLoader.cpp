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
#include "PngLoader.h"

void PngLoader::getAssetStream(AAssetManager* mgr, const char* fileName, std::vector<char> &buffer)
{
    AAsset* asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    if(!asset) {
        return;
    }
    off_t fileSize = AAsset_getLength(asset);
    buffer.resize(fileSize);
    AAsset_read(asset, &buffer[0], fileSize);
    AAsset_close(asset);
}

void PngLoader::readFileCallback(png_structp png_ptr, png_bytep destination, png_size_t bytesToRead)
{
    png_voidp io_ptr = png_get_io_ptr( png_ptr );
    if( io_ptr == 0 ) {
        return;
    }

    png_voidp a = png_get_io_ptr(png_ptr);
    //Cast the pointer to std::istream* and read 'bytesToRead' bytes into 'destination'
    ((std::istream*)a)->read((char*)destination, bytesToRead);
}

GLuint* PngLoader::loadPngData(AAssetManager* mgr, const char* fileName, int* textureWidth, int* textureHeight)
{
    if (fileName == nullptr) {
        return nullptr;
    }

    std::vector<char> buffer;
    getAssetStream(mgr, fileName, buffer);
    std::string pngDataString;
    for (int i = 0; i < buffer.size(); ++i) {
       pngDataString += buffer[i];
    }
    std::istringstream pngDataStream0(pngDataString);

    std::istream &pngDataStream = pngDataStream0;
    const int PNG_SIG_BYTES = 8;
    char pngSignature[PNG_SIG_BYTES];
    pngDataStream.read(pngSignature, PNG_SIG_BYTES * sizeof(char));

    if(!png_check_sig( (png_bytep)pngSignature, PNG_SIG_BYTES) ) {
        return nullptr;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        return nullptr;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return nullptr;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return nullptr;
    }

    png_set_read_fn(png_ptr, (void*)&pngDataStream, readFileCallback);

    png_set_sig_bytes( png_ptr, 8 );

    png_read_info( png_ptr, info_ptr);

    int _width, _height, _depth;
    bool _hasAlpha;
    int color_type, interlace_type;

    png_get_IHDR( png_ptr, info_ptr, (png_uint_32*)&_width, (png_uint_32*)&_height, &_depth, &color_type, &interlace_type, NULL, NULL );

    switch(color_type) {
        case PNG_COLOR_TYPE_RGB:
            _hasAlpha = false;
            break;
        case PNG_COLOR_TYPE_RGBA:
            _hasAlpha = true;
            break;
        default:
            return nullptr;
    }

    png_size_t cols = png_get_rowbytes(png_ptr, info_ptr);

    png_bytepp row_pp = new png_bytep[_height];
    char * bitmapData = new char[ cols * _height ];

    for( int i = 0; i < _height; ++i ) {
        row_pp[_height - i - 1] = (png_bytep)&((char *)bitmapData)[ i * cols ];
    }

    png_read_image( png_ptr, row_pp );
    png_read_end( png_ptr, info_ptr );

    png_destroy_read_struct( &png_ptr, &info_ptr, 0 );

    delete [] row_pp;

    *textureWidth   = _width;
    *textureHeight  = _height;
    return (GLuint*)bitmapData;
}
