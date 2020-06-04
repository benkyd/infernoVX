#include "scene.hpp"

#include "voxel.hpp"
#include "utilities.hpp"

Scene::Scene()
{

}

void Scene::Load()
{
	// load voxel scene into memory and create a mesh and send it to the gpu

	// temporary
	Dimensions = { 10, 10, 10 };





}

void Scene::OpenGLDraw()
{

}

int Scene::mIndex( int x, int y, int z )
{
	return x + Dimensions.x * (y + Dimensions.z * z);
}

Scene::~Scene()
{

}
