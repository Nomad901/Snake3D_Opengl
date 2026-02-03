#include "snkpch.h"
#include "Engine/Model/Mesh/StaticMesh.h"

#include "Engine/Model/Mesh/Vertex.h"
#include "Engine/Model/Buffers/VBOLayout.h"
#include "Engine/Model/Mesh/Texture.h"

namespace SnakeEngine
{
	void StaticMesh::init(const std::vector<SnakeEngine::Vertex>& pVertices,
						  const std::vector<uint32_t>& pIndices, 
						  std::vector<Texture>& pTextures)
	{
		mIndices = pIndices;
		mTextures = std::move(pTextures);

		loadMesh(pVertices);
	}
	void StaticMesh::draw()
	{
		mVAO.bind();
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	}
	std::vector<Texture>& StaticMesh::getTextures() noexcept
	{
		return mTextures;
	}
	void StaticMesh::loadMesh(const std::vector<SnakeEngine::Vertex>& pVertices)
	{
		VBOLayout vboLayout;
		VBO vbo;

		mVAO.generate();
		mVAO.bind();
		vbo.init(pVertices.data(), pVertices.size() * sizeof(SnakeEngine::Vertex), GL_STATIC_DRAW);
		vboLayout.pushLayout(GL_FLOAT, 3);
		vboLayout.pushLayout(GL_FLOAT, 3);
		vboLayout.pushLayout(GL_FLOAT, 2);
		mVAO.addBuffer(vboLayout);
		mEBO.init(mIndices.data(), mIndices.size());
	}
}