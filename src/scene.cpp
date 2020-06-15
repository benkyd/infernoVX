#include "scene.hpp"

#include <logger.h>
#include <iostream>

#include "voxel.hpp"
#include "utilities.hpp"

#include "shader.hpp"
#include "camera.hpp"

Scene::Scene()
{

}

void loadScene(glm::vec3* dimensions, uint8_t*& voxels)
{
	*dimensions = glm::vec3 { 100, 100, 100 };
	
	voxels = (uint8_t*)malloc( sizeof( uint8_t ) * (static_cast<size_t>(dimensions->x)
											      * static_cast<size_t>(dimensions->y)
											      * static_cast<size_t>(dimensions->z) ) );
	memset(voxels, 0, (static_cast<size_t>(dimensions->x)
				     * static_cast<size_t>(dimensions->y)
					 * static_cast<size_t>(dimensions->z) ) );

	for ( int x = 0; x < dimensions->x; x++ )
	for ( int y = 0; y < dimensions->y; y++ )
	for ( int z = 0; z < dimensions->z; z++ )
	{
		if ( (rand() % 2) != 0 )
		{
			voxels[Index3D( x, y, z, dimensions->x, dimensions->y, dimensions->z )] = (uint8_t)1;
		}
		else
		{
			voxels[Index3D( x, y, z, dimensions->x, dimensions->y, dimensions->z )] = (uint8_t) 0;
		}
	}

}

void Scene::Load()
{
	
	Logger logger;

	// loadScene passes ownership, scene's job to clean up
	loadScene(&Dimensions, Voxels); // TODO: import actual voxel scenes

	logger << LOGGER_INFO << "Scene loaded" << LOGGER_ENDL;

	// model matrix
	mModel = glm::mat4( 1.0f );

	for ( int x = 0; x < Dimensions.x; x++ )
	for ( int y = 0; y < Dimensions.y; y++ )
	for ( int z = 0; z < Dimensions.z; z++ )
	{

		uint8_t block = VoxelAt( x, y, z );

		if ( block == 0 ) continue;

		Voxel* tmp = new Voxel( { x, y, z }, block );

		if ( VoxelAt( x + 1, y, z ) == 0 )
			tmp->AddFace( EFaceType::Right );

		if ( VoxelAt( x - 1, y, z ) == 0 )
			tmp->AddFace( EFaceType::Left );

		if ( VoxelAt( x, y + 1, z ) == 0 )
			tmp->AddFace( EFaceType::Top );

		if ( VoxelAt( x, y - 1, z ) == 0 )
			tmp->AddFace( EFaceType::Bottom );

		if ( VoxelAt( x, y, z + 1 ) == 0 )
			tmp->AddFace( EFaceType::Front );

		if ( VoxelAt( x, y, z - 1 ) == 0 )
			tmp->AddFace( EFaceType::Back );

		std::vector<glm::vec3> tempVerts;
		std::vector<glm::vec3> tempUVs;
		tmp->GetMesh( tempVerts, tempUVs );
		
		mVertices.insert( mVertices.end(), tempVerts.begin(), tempVerts.end() );
		mUvs.insert( mUvs.end(), tempUVs.begin(), tempUVs.end() );

		delete tmp;

		tempVerts.clear();
		tempUVs.clear();
	}

	logger << LOGGER_INFO << "Scene mesh built" << LOGGER_ENDL;

	glGenVertexArrays( 1, &mVao );
	glBindVertexArray( mVao );

	glGenBuffers( 1, &mVbo );
	glBindBuffer( GL_ARRAY_BUFFER, mVbo );

	std::vector<glm::vec3> data;
	data.insert( data.end(), mVertices.begin(), mVertices.end() );
	data.insert( data.end(), mUvs.begin(), mUvs.end() );

	logger << LOGGER_DEBUG << "The following 3 values are the verts and uvs sent to the gpu" << LOGGER_ENDL;
	logger << LOGGER_DEBUG << mVertices.size() << LOGGER_ENDL;
	logger << LOGGER_DEBUG << mUvs.size() << LOGGER_ENDL;
	logger << LOGGER_DEBUG << data.size() << LOGGER_ENDL;

	mNumVerts = mVertices.size();

	glBufferData( GL_ARRAY_BUFFER, data.size() * sizeof( glm::vec3 ), &data[0], GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0 );

	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (const void*)(mVertices.size() * sizeof( glm::vec3 )) );

	mVertices.clear();
	mUvs.clear();

	data.clear();

	glBindVertexArray( 0 );

	logger << LOGGER_INFO << "Scene mesh built and sent to the GPU" << LOGGER_ENDL;

}

void Scene::OpenGLDraw( Camera* camera, Shader* shader )
{
	shader->Use();
	glBindVertexArray( mVao );

	GLint uniTrans = glGetUniformLocation( shader->Program, "Model" );
	glUniformMatrix4fv( uniTrans, 1, GL_FALSE, glm::value_ptr( mModel ) );

	GLint uniView = glGetUniformLocation( shader->Program, "View" );
	glUniformMatrix4fv( uniView, 1, GL_FALSE, glm::value_ptr( camera->GetViewMatrix() ) );

	GLint uniProj = glGetUniformLocation( shader->Program, "Proj" );
	glUniformMatrix4fv( uniProj, 1, GL_FALSE, glm::value_ptr( camera->GetProjectionMatrix() ) );

	glDrawArrays( GL_TRIANGLES, 0, mNumVerts );

}

uint8_t Scene::VoxelAt( int x, int y, int z )
{
	if ( x > Dimensions.x - 1 ) return 0;
	if ( y > Dimensions.y - 1 ) return 0;
	if ( z > Dimensions.z - 1 ) return 0;

	if ( x < 0 ) return 0;
	if ( y < 0 ) return 0;
	if ( z < 0 ) return 0;

	return Voxels[mIndex( x, y, z )];
}

int Scene::mIndex( int x, int y, int z )
{
	return Index3D( x, y, z, Dimensions.x, Dimensions.y, Dimensions.z );
}

Scene::~Scene()
{
	delete[] Voxels;
}
