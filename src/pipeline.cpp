#include "pipeline.hpp"

#include "camera.hpp"
#include "display.hpp"

#include "scene.hpp"

#include "utilities.hpp"

Pipeline::Pipeline( Display* display, Camera* camera )
{
	mCamera = camera;

	mScene = new Scene();
	mScene->Load();

	DrawQuadShader.Load( std::string( _RESOURCES ) + "drawquad" );
	DrawQuadShader.Link();

	DefferedShader.Load( std::string( _RESOURCES ) + "deferred" );
	DefferedShader.Link();

	GBuffer.Init( display->GetDisplaySizePx().x, display->GetDisplaySizePx().y );

	// settup drawing surface
	// this will need UVs lol
	static const float vertices[] = {
		-1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );

	glEnableVertexAttribArray( 0 );

}

void Pipeline::NextFrame( Display* display )
{
	display->PrepareFrame();
	glCheckError();

	glEnable( GL_DEPTH_TEST );
	glCheckError();

	GBuffer.BindWrite();
	glCheckError();

	mScene->RenderScene( mCamera, &DefferedShader );
	glCheckError();

	glBindFramebuffer( GL_FRAMEBUFFER, 0 ); // back to default
	glCheckError();

	// this wont actually render the gbuffer textcoord texture
	// because there isnt UVs for the screen quad lmao
	// its just verts
	glBindVertexArray( VAO );
	glCheckError();

	// DrawQuadShader.Bind();
	glCheckError();

	// GBuffer.BindReadBuffer( EGBufferType::TexCoord );
	glCheckError();

	glBindTexture( GL_TEXTURE_2D, GBuffer.GetTexture( EGBufferType::TexCoord ) );
	glCheckError();

	glDrawArrays( GL_TRIANGLES, 0, 6 );
	glCheckError();


	DrawQuadShader.UnBind();
	glCheckError();

	display->NextFrame();
	glCheckError();
}
