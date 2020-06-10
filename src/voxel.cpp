#include "voxel.hpp"

Voxel::Voxel( glm::vec3 coordsInChunk, uint8_t block )
{

	// Texture winding order - top, bottom, left, right, front, back

	Type = block;
	mPosition = coordsInChunk;

}

void Voxel::AddFace( EFaceType::Face face )
{

	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;

	switch ( face )
	{

	case EFaceType::Top:
	{

		verts = CubeTopFace;
		uvs = CubeTopFaceUVs;

		break;
	}

	case EFaceType::Bottom:
	{

		verts = CubeBottomFace;
		uvs = CubeBottomFaceUVs;

		break;
	}

	case EFaceType::Left:
	{

		verts = CubeLeftFace;
		uvs = CubeLeftFaceUVs;

		break;
	}

	case EFaceType::Right:
	{

		verts = CubeRightFace;
		uvs = CubeRightFaceUVs;

		break;
	}

	case EFaceType::Front:
	{

		verts = CubeFrontFace;
		uvs = CubeFrontFaceUVs;

		break;
	}

	case EFaceType::Back:
	{

		verts = CubeBackFace;
		uvs = CubeBackFaceUVs;

		break;
	}

	}


	verts = mTranslateIntoWorld( verts, mPosition );
	mVertices.insert( mVertices.end(), verts.begin(), verts.end() );

	// std::shared_ptr<CBlockEntry> block = CBlockDictionary::GetInstance()->BlockEntries[Block];

	// uint16_t tex = block->FaceTextures[(uint16_t) face];

	uint16_t tex = 1;

	std::vector<glm::vec3> uvws = {
		{ uvs[0].x, uvs[0].y, (float) tex },
		{ uvs[1].x, uvs[1].y, (float) tex },
		{ uvs[2].x, uvs[2].y, (float) tex },
		{ uvs[3].x, uvs[3].y, (float) tex },
		{ uvs[4].x, uvs[4].y, (float) tex },
		{ uvs[5].x, uvs[5].y, (float) tex },
	};

	mUvs.insert( mUvs.end(), uvws.begin(), uvws.end() );

}

void Voxel::GetMesh( std::vector<glm::vec3>& verts, std::vector<glm::vec3>& uvs )
{
	verts = mVertices;
	uvs = mUvs;
}

void Voxel::Clear()
{

	mVertices.clear();
	mUvs.clear();

}

std::vector<glm::vec3> Voxel::mTranslateIntoWorld( std::vector<glm::vec3> verts, glm::vec3 trans )
{

	for ( int i = 0; i < verts.size(); i++ )
	{

		verts[i].x += trans.x;
		verts[i].y += trans.y;
		verts[i].z += trans.z;

	}

	return verts;

}

Voxel::~Voxel()
{
	mVertices.clear();
	mUvs.clear();
}
