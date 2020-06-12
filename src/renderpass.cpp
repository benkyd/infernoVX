#include "renderpass.hpp"

#include "camera.hpp"
#include "display.hpp"

#include "scene.hpp"


Pipeline::Pipeline( Camera* camera )
	: RasterPass()
{
	mCamera = camera;

	mScene = new Scene();
	mScene->Load();

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

	// mScene->OpenGLDraw( mCamera, );



	// glDrawArrays( GL_TRIANGLES, 0, 6 );


}
