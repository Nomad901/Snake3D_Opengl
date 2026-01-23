#include "snkpch.h"
#include "Engine/Model/Mesh/Mesh.h"

#include "Engine/Model/Mesh/Vertex.h"
#include "Engine/Model/Buffers/VBOLayout.h"

namespace SnakeEngine
{
	void Mesh::init(const std::vector<SnakeEngine::Vertex>& pVertices,
					const std::vector<uint32_t>& pIndices)
	{
		VBOLayout vboLayout;
		VBO vbo;

		mVAO.generate();
		mVAO.bind();
		vbo.init(pVertices, GL_STATIC_DRAW);
		vboLayout.pushLayout(GL_FLOAT, 3);
		vboLayout.pushLayout(GL_FLOAT, 3);
		vboLayout.pushLayout(GL_FLOAT, 2);
		mVAO.addBuffer(vboLayout);
		mEBO.init(pIndices.data(), pIndices.size());
	}
	void Mesh::draw()
	{
		mVAO.bind();
		glDrawElements(GL_TRIANGLES, mEBO.getCount(), GL_UNSIGNED_INT, nullptr);
	}
}