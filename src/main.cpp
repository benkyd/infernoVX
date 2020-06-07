#include <iostream>
#include <sstream>

#define LOGGER_DEFINITION
#include <logger.h>

#if _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "display.hpp"
#include "settings.hpp"

#include "scene.hpp"

#include "shader.hpp"
#include "camera.hpp"

#define __DEBUG

static const int VERSION_MAJOR = 1;
static const int VERSION_MINOR = 1;
static const int VERSION_PATCH = 0;

void version()
{
	std::stringstream version;

	auto& container = []( std::string s ) { std::string r = ""; for ( auto& c : s ) { r += "-"; } return r; };

	version << "InfernoVX ";
	version << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;

	std::cout << container( version.str() ) << std::endl;
	std::cout << version.str() << std::endl;
	std::cout << container( version.str() ) << std::endl;
}

void Loop( Display* display )
{
	SDL_Event e;

	// settup drawing surface
	float vertices[] = {
		-1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f
	};

	GLuint VAO;
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
	GLuint VBO;
	glGenBuffers( 1, &VBO );
	glBindBuffer( GL_ARRAY_BUFFER, VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*) 0 );
	glEnableVertexAttribArray( 0 );

	// settup shader
	Shader raytracer;
	raytracer.Load( ResourceBase + "tracer" );
	raytracer.Link();
	raytracer.Use();

	GLint uResolution = glGetUniformLocation( raytracer.Program, "vResolution" );

	glm::vec2 resolution = display->GetDisplaySizePx();
	glUniform3i( uResolution, resolution.x, resolution.y, 0 );


	Shader drawshader;
	drawshader.Load( ResourceBase + "simpleraster" );
	drawshader.Link();

	Camera camera { static_cast<int>(resolution.x), static_cast<int>(resolution.y) };

	Scene scene;
	scene.Load();

	int i = 0;
	while ( display->IsWindowOpen )
	{
		i++;
		display->PrepareFrame();

		// return window size
		bool didResize = display->Input( &e, &camera );
		if ( didResize )
		{
			resolution = display->GetDisplaySizePx();
			camera.UpdateProjection( resolution.x, resolution.y );
			glUniform3i( uResolution, resolution.x, resolution.y, 0 );
		}


		// rendering here

		scene.OpenGLDraw( &camera, &drawshader );

		// glDrawArrays( GL_TRIANGLES, 0, 6 );

		display->NextFrame();
	}

	// cleanup

}

int main( int argc, char** argv )
{
	version();

	Logger mLogger;
	
#ifdef __DEBUG
	mLogger << LOGGER_DEBUG << "Debug mode enabled" << LOGGER_ENDL;
#endif

	// settup display

	std::stringstream version;
	version << "InfernoVX ";
	version << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH;

	Display display { WindowWidth, WindowHeight, version.str() };

	Loop( &display );

	return 0;

}
