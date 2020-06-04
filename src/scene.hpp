#ifndef INFERNOVX_SCENE_H_
#define INFERNOVX_SCENE_H_

#include <stdint.h>
#include <vector>

#include <glm/glm.hpp>

class Voxel;

// TODO: sky class
class Sky
{

};

class Scene
{
public:

	Scene();

	// TODO: look into voxel storage formats
	void Load();

	void OpenGLDraw();

	// scene
	glm::vec3 Dimensions;
	// voxel data (indexed [x + WIDTH * (y + DEPTH * z)])
	Voxel* Voxels;

	~Scene();

private:

	// mesh data
	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mUvs;
	int m_numVerts = 0;
	glm::mat4 mModel;

	int mIndex( int x, int y, int z );

};

#endif
