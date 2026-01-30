#include "snkpch.h"
#include "Engine/Model/Mesh/DynamicMesh.h"
#include "Engine/Model/Mesh/Mesh.h"

#include "Engine/Model/Mesh/BoneVertex.h"
#include "Engine/Model/Buffers/VBOLayout.h"
#include "Engine/Model/Mesh/Texture.h"

namespace SnakeEngine
{
	void DynamicMesh::init(const std::vector<SnakeEngine::BoneVertex>& pVertices, 
						   const std::vector<uint32_t>& pIndices, 
						   const std::vector<Texture>& pTextures)
	{
	}
	void DynamicMesh::draw()
	{
	}
	void DynamicMesh::destroy()
	{

	}
	const std::vector<Texture>& DynamicMesh::getTextures() const noexcept
	{
		return mTextures;
	}
	void DynamicMesh::loadMesh(const std::vector<SnakeEngine::BoneVertex>& pVertices)
	{
	}
}