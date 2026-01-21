#include "snkpch.h"
#include "Engine/Mesh/EBO.h"

namespace SnakeEngine
{
	EBO::~EBO()
	{
		destroy();
	}
	void EBO::init(const void* pData, uint32_t pCount)
	{
	}
	void EBO::destroy()
	{
		glDeleteBuffers(1, &mEBOid);
	}
	void EBO::bind()
	{
		glBindBuffer(GL_INDEX_ARRAY, mEBOid);
	}
	void EBO::unbind()
	{
		glBindBuffer(GL_INDEX_ARRAY, 0);
	}
	uint32_t EBO::getCount() const noexcept
	{
		return mCount;
	}
	uint32_t EBO::getEBOid() const noexcept
	{
		return mEBOid;
	}
}