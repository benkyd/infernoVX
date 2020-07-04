#ifndef INFERNOVX_UTILITIES_H_
#define INFERNOVX_UTILITIES_H_

#include <glad/glad.h>
#include <string>

#include <logger.h>

#ifndef glCheckError()
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#endif

static Logger logger;

inline GLenum glCheckError_( const char* file, int line )
{
	GLenum errorCode;
	while ( (errorCode = glGetError()) != GL_NO_ERROR )
	{
		std::string error;
		switch ( errorCode )
		{
			case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		logger << LOGGER_ERROR << "OpenGL Error: " << error << " | " << file << " (" << line << ")" << LOGGER_ENDL;
	}
	return errorCode;
}

#include <fstream>

inline std::string LoadTextFromFile( std::string file )
{
	std::ifstream t( file );
	std::string text( (std::istreambuf_iterator<char>( t )),
		std::istreambuf_iterator<char>() );
	return text;
}

inline int Index3D( int x, int y, int z, int width, int height, int depth )
{
	return x + y * width + z * depth * height;
}

// credit to EntireTwix#0434 (William)
// #define __cpp_lib_concepts
#include <concepts>
#include <vector>

/*
template <typename T>
concept EqualityComparable = requires(T a, T b)
{
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};

template <EqualityComparable T>
inline bool VectorContains( const std::vector<T>& vec, T value )
{
	if constexpr ( std::is_fundamental<T>::value ) for ( T t : vec ) if ( t == value ) return true;
	else for ( const T& t : vec ) if ( t == value ) return true;
	return false;
}*/

#endif
