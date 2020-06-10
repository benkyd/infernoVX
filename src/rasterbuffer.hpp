#ifndef INFERNOVX_RASTERBUFFER_H_
#define INFERNOVX_RASTERBUFFER_H_

#include <stdint.h>

#include <glad/glad.h>

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

private:

    GLuint mFbo;
    GLuint mTextures[EGBufferType::COUNT];
    GLuint mDepthTexture;
};

#endif
