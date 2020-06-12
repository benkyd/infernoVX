#ifndef INFERNOVX_RASTERBUFFER_H_
#define INFERNOVX_RASTERBUFFER_H_

#include <stdint.h>

#include <glad/glad.h>

#include "shader.hpp"

class RasterRenderer
{
public:

    RasterRenderer();



    Shader DefferedShader;

};


// implements a basic G-Buffer for deffered rendering

namespace EGBufferType
{
    // Will need more information regarding the surface of hit
    // depth texture is handled seperately
    enum TextureType : uint8_t
    {
        GLPosition,
        Albedo,
        SurfaceNormal,
        TexCoord,
        COUNT
    };
}

class RasterBuffer
{
public:

    RasterBuffer();

    void Init( int RenderWidth, int RenderHeight );

    void Resize( int RenderWidth, int RenderHeight );

    void BindWrite();
    void BindRead();

    ~RasterBuffer();

    GLuint FBO;

private:

    GLuint mTextures[EGBufferType::COUNT];
    GLuint mDepthTexture;
};

#endif
