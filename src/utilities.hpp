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

inline int Index3D( int x, int y, int z, int width, int height, int depth )
{
	return x + y * width + z * depth * height;
}


// credit to EntireTwix#0434 (William)
#define __cpp_lib_concepts
#include <concepts>
#include <vector>

template <typename T>
concept EqualityComparable = requires(T a, T b)
{
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};

template <EqualityComparable T>
bool VectorContains( const std::vector<T>& vec, T value )
{
	if constexpr ( std::is_fundamental<T>::value ) for ( T t : vec ) if ( t == value ) return true;
	else for ( const T& t : vec ) if ( t == value ) return true;
	return false;
}

#endif
