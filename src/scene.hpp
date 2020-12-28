#ifndef INFERNOVX_SCENE_H_
#define INFERNOVX_SCENE_H_

#include <stdint.h>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Voxel;

class Camera;
class Shader;

// TODO: sky class
class Sky
{

};

class Scene
{
public:

	Scene();

	// TODO: look into voxel storage formats
	// load voxel scene into memory and create 
	// a mesh and send it to the gpu
	void Load();

	void RenderScene( Camera* camera, Shader* shader );

	// scene
	glm::vec3 Dimensions;
	// voxel data (indexed [x + WIDTH * (y + DEPTH * z)])
	uint8_t VoxelAt( int x, int y, int z );
	uint8_t* Voxels;

	~Scene();

private:

	int mIndex( int x, int y, int z );

	// mesh data
	// for mesh generation only too much 
	// memory if theyre kept
	std::vector<glm::vec3> mVertices;
	std::vector<glm::vec3> mUvs;
	std::vector<glm::vec3> mNormals;
	int mNumVerts = 0;

	// OpenGL stuff
	GLuint mVao = 0;
	GLuint mVbo = 0;
	glm::mat4 mModel;

};

#endif
