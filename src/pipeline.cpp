#include "pipeline.hpp"

#include "camera.hpp"
#include "display.hpp"

#include "scene.hpp"

#include "utilities.hpp"

Pipeline::Pipeline( Display* display, Camera* camera )
	: DrawQuadShader(),
	  DefferedShader()
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
	float vertices[] = {
	//  Position              Texcoords
		-1.0f,  1.0f, 0.0f,   0.0f, 0.0f, // Top-left
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, // Top-right
		 1.0f, -1.0f, 0.0f,   1.0f, 1.0f, // Bottom-right
		-1.0f, -1.0f, 0.0f,   0.0f, 1.0f  // Bottom-left
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};


	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );

	glGenBuffers( 1, &EBO );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), 0 );
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)(3 * sizeof( float )) );

	glEnableVertexAttribArray( 0 );

}

void Pipeline::NextFrame( Display* display )
{
	display->PrepareFrame();
	
	GBuffer.BindWrite();
	mScene->RenderScene( mCamera, &DefferedShader );
	GBuffer.UnBind();


	glBindVertexArray( VAO );
	DrawQuadShader.Bind();

	// GBuffer.BindRead();
	// GBuffer.BindReadBuffer( EGBufferType::TexCoord );
	
	glBindTexture( GL_TEXTURE_2D, GBuffer.GetTexture( EGBufferType::TexCoord ) );

	glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
	DrawQuadShader.UnBind();

	glCheckError();
	display->NextFrame();	
}
