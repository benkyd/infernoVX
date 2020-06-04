#include "rasterbuffer.hpp"

#include <logger.h>

RasterBuffer::RasterBuffer()
{

}

void RasterBuffer::Init( int RenderWidth, int RenderHeight )
{
    Logger logger;

	glGenFramebuffers( 1, &mFbo );
	glBindFramebuffer( GL_DRAW_FRAMEBUFFER, mFbo );

	glGenTextures( EGBufferType::COUNT, mTextures );
	glGenTextures( 1, &mDepthTexture );

    for ( unsigned int i = 0; i < EGBufferType::COUNT; i++ )
    {
        glBindTexture( GL_TEXTURE_2D, mTextures[i] );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32F, RenderWidth, RenderHeight, 0, GL_RGB, GL_FLOAT, NULL );
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mTextures[i], 0 );
    }

    // depth
    glBindTexture( GL_TEXTURE_2D, mDepthTexture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, RenderWidth, RenderHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL );
    glFramebufferTexture2D( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTexture, 0 );

    // same ammount here as EGBufferType
    GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
    glDrawBuffers( EGBufferType::COUNT, drawBuffers );

    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );

    if ( status != GL_FRAMEBUFFER_COMPLETE )
    {
        logger << LOGGER_PANIC << "Could not validate framebuffer: " << status << LOGGER_ENDL;
    }

    // put back the default framebuffer
    glBindFramebuffer( GL_DRAW_FRAMEBUFFER, 0 );

}

void RasterBuffer::Resize( int RenderWidth, int RenderHeight )
{
    // TODO
}

void RasterBuffer::BindWrite()
{

}

void RasterBuffer::BindRead()
{

}

RasterBuffer::~RasterBuffer()
{

}
