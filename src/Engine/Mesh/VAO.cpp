#include "snkpch.h"
#include "Engine/Mesh/VAO.h"

namespace SnakeEngine
{
	VAO::~VAO()
	{
		destroy();
	}
	void VAO::addBuffer(VBOLayout& pVBOLayout)
	{
		bind();

	}
	void VAO::destroy()
	{
		glDeleteVertexArrays(1, &mVAOid);
	}
	void VAO::generate()
	{
		glGenVertexArrays(1, &mVAOid);
	}
	void VAO::bind()
	{
		glBindBuffer(GL_VERTEX_ARRAY, mVAOid);
	}
	void VAO::unbind()
	{
		glBindBuffer(GL_VERTEX_ARRAY, 0);
	}
	uint32_t SnakeEngine::VAO::getVAOid() const noexcept
	{
		return mVAOid;
	}
}
