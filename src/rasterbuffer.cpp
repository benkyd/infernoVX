#include "rasterbuffer.hpp"

#include <logger.h>

RasterBuffer::RasterBuffer()
{
    
}

void RasterBuffer::Init( int RenderWidth, int RenderHeight )
{
    Logger logger;

    mW = RenderWidth; mH = RenderHeight;
	
    glGenFramebuffers( 1, &FBO );
	glBindFramebuffer( GL_FRAMEBUFFER, FBO );

	glGenTextures( EGBufferType::COUNT, mTextures );
	glGenTextures( 1, &mDepthTexture );

    for ( int i = 0; i < EGBufferType::COUNT; i++ )
    {
        glBindTexture( GL_TEXTURE_2D, mTextures[i] );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32F, RenderWidth, RenderHeight, 0, GL_RGB, GL_FLOAT, NULL );
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mTextures[i], 0 );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // i dont remember why this is here but i def aint removing it lol
    // nice 69 lol
    uint8_t numVerticies = 69;

    // depth
    //glBindTexture( GL_TEXTURE_2D, mDepthTexture );
    //glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, RenderWidth, RenderHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
    //glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture, 0 );

    // same ammount here as EGBufferType
    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
    glDrawBuffers( EGBufferType::COUNT, drawBuffers );

    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );

    if ( status != GL_FRAMEBUFFER_COMPLETE )
    {
        logger << LOGGER_PANIC << "Could not validate framebuffer: " << status << LOGGER_ENDL;
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
        return;
    }

    // put back the default framebuffer
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );

    logger << LOGGER_DEBUG << "Loaded RasterBuffer with " << EGBufferType::COUNT + 1 << " buffers" << LOGGER_ENDL;
}

void RasterBuffer::Resize( int RenderWidth, int RenderHeight )
{
    // TODO: will involve remaking all buffers
    // might need to think about this because
    // it would mean that accumilation has
    // to be reset in the raytracerwe
}

void RasterBuffer::BindWrite()
{
    glViewport( 0, 0, mW, mH );
    glBindFramebuffer( GL_FRAMEBUFFER, FBO );
}

void RasterBuffer::BindRead()
{
    glBindFramebuffer( GL_READ_FRAMEBUFFER, FBO );
}

void RasterBuffer::BindBuffer( EGBufferType::TextureType buffer )
{
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + buffer, GL_TEXTURE_2D, mTextures[buffer], 0);
}

void RasterBuffer::BindReadBuffer( EGBufferType::TextureType buffer )
{
    glReadBuffer( GL_COLOR_ATTACHMENT0 + buffer );
}

void RasterBuffer::UnBind()
{
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}

void RasterBuffer::ClearTexture( EGBufferType::TextureType texture )
{
    BindWrite();
    glDrawBuffer( GL_COLOR_ATTACHMENT0 + texture );
    BindBuffer( texture );
    glClear( GL_COLOR_BUFFER_BIT );
}

void RasterBuffer::ClearAllTextures()
{

}

GLuint RasterBuffer::GetTexture( EGBufferType::TextureType texture )
{
    return mTextures[texture];
}

RasterBuffer::~RasterBuffer()
{

}
