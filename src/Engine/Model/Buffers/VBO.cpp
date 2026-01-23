#include "snkpch.h"
#include "Engine/Mesh/VBO.h"

namespace SnakeEngine
{
	SnakeEngine::VBO::~VBO()
	{
		destroy();
	}
	void VBO::init(const std::vector<Vertex>& pData, GLenum pUsage)
	{
		glGenBuffers(1, &mVBOid);
		glBindBuffer(GL_ARRAY_BUFFER, mVBOid);
		glBufferData(GL_ARRAY_BUFFER, pData.size() * sizeof(Vertex), pData.data(), pUsage);
	}
	void VBO::init(const void* pData, GLuint pSize, GLenum pUsage)
	{
		glGenBuffers(1, &mVBOid);
		glBindBuffer(GL_ARRAY_BUFFER, mVBOid);
		glBufferData(GL_ARRAY_BUFFER, pSize, pData, pUsage);
	}
	void VBO::destroy()
	{
		glDeleteBuffers(1, &mVBOid);
	}
	void VBO::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVBOid);
	}
	void VBO::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	uint32_t VBO::getVBOid() const noexcept
	{
		return mVBOid;
	}
}
