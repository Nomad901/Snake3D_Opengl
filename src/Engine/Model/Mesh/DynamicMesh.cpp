#include "snkpch.h"
#include "Engine/Model/Mesh/DynamicMesh.h"

#include "Engine/Model/Buffers/VBOLayout.h"
#include "Engine/Model/Mesh/Texture.h"

namespace SnakeEngine
{
	void DynamicMesh::init(const std::vector<SnakeEngine::BoneVertex>& pVertices, 
						   const std::vector<uint32_t>& pIndices, 
						   std::vector<Texture>& pTextures)
	{
		mIndices = pIndices;
		mTextures = std::move(pTextures);

		loadMesh(pVertices);
	}
	void DynamicMesh::draw()
	{
		mVAO.bind();
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	}
	std::vector<SnakeEngine::Texture>& DynamicMesh::getTextures() noexcept
	{
		return mTextures;
	}
	void DynamicMesh::loadMesh(const std::vector<SnakeEngine::BoneVertex>& pVertices)
	{
		VBOLayout vboLayout;
		VBO vbo;

		mVAO.generate();
		mVAO.bind();
		vbo.init(pVertices.data(), pVertices.size() * sizeof(SnakeEngine::BoneVertex), GL_STATIC_DRAW);
		vboLayout.pushLayout(GL_FLOAT, 3);
		vboLayout.pushLayout(GL_FLOAT, 3);
		vboLayout.pushLayout(GL_FLOAT, 2);
		vboLayout.pushLayout(GL_INT, 4);
		vboLayout.pushLayout(GL_FLOAT, 4);
		mVAO.addBuffer(vboLayout);
		mEBO.init(mIndices.data(), mIndices.size());
	}
}