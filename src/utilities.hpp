#ifndef INFERNOVX_UTILITIES_H_
#define INFERNOVX_UTILITIES_H_

#include <fstream>
#include <string>

inline std::string LoadTextFromFile( std::string file )
{
	std::ifstream t( file );
	std::string text( (std::istreambuf_iterator<char>( t )),
		std::istreambuf_iterator<char>() );
	return text;
}

#include <glm/glm.hpp>

inline int Index3D( int x, int y, int z, int width, int height, int depth )
{
	return x + y * width + z * depth * height;
}

#endif
