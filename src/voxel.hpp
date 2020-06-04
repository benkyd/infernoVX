#ifndef INFERNOVX_VOXEL_H_
#define INFERNOVX_VOXEL_H_

#include <stdint.h>
#include <vector>

#include <glm/glm.hpp>


namespace EFaceType 
{
	enum Face : uint8_t 
	{
		Top,
		Bottom,
		Left,
		Right,
		Front,
		Back,
	};
}

static std::vector<glm::vec3> CubeTopFace = 
{
	{ -0.5f,  0.5f, -0.5f },
	{  0.5f,  0.5f, -0.5f },
	{  0.5f,  0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f, -0.5f }
};

static std::vector<glm::vec2> CubeTopFaceUVs = 
{
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeBottomFace = 
{
	{ -0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f, -0.5f,  0.5f },
	{ -0.5f, -0.5f,  0.5f },
	{ -0.5f, -0.5f, -0.5f }
};

static std::vector<glm::vec2> CubeBottomFaceUVs = 
{
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeLeftFace = 
{
	{ -0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f },
	{ -0.5f, -0.5f,  0.5f },
	{ -0.5f,  0.5f,  0.5f }
};

static std::vector<glm::vec2> CubeLeftFaceUVs = 
{
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeRightFace = 
{
	{  0.5f,  0.5f,  0.5f },
	{  0.5f,  0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
};

static std::vector<glm::vec2> CubeRightFaceUVs = 
{
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f },
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f }
};

static std::vector<glm::vec3> CubeFrontFace = 
{
	{ -0.5f, -0.5f,  0.5f },
	{  0.5f, -0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
	{  0.5f,  0.5f,  0.5f },
	{ -0.5f,  0.5f,  0.5f },
	{ -0.5f, -0.5f,  0.5f }
};

static std::vector<glm::vec2> CubeFrontFaceUVs = 
{
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f }
};

static std::vector<glm::vec3> CubeBackFace = 
{
	{ -0.5f, -0.5f, -0.5f },
	{  0.5f, -0.5f, -0.5f },
	{  0.5f,  0.5f, -0.5f },
	{  0.5f,  0.5f, -0.5f },
	{ -0.5f,  0.5f, -0.5f },
	{ -0.5f, -0.5f, -0.5f }
};

static std::vector<glm::vec2> CubeBackFaceUVs = 
{
	{ 1.0f, 1.0f },
	{ 0.0f, 1.0f },
	{ 0.0f, 0.0f },
	{ 0.0f, 0.0f },
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f }
};

class Voxel 
{
public:
	Voxel( glm::vec3 coords, uint8_t type );

	// There's no check on this, if it's called twice 
	// for the same face there will be a duplicate in
	// the mesh, cba to add ones
	void AddFace( EFaceType::Face face );
	void GetMesh( std::vector<glm::vec3>& verts, std::vector<glm::vec3>& uvs );

	void Clear();

	uint8_t Type;

private:

	glm::vec3 mPosition;

	std::vector<glm::vec3> mTranslateIntoWorld( std::vector<glm::vec3> verts, glm::vec3 trans );

	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mUvs;

};

#endif
