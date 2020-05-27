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

#endif
