#include "snkpch.h"
#include "Engine/Model/Buffers/EBO.h"

namespace SnakeEngine
{
	EBO::~EBO()
	{
		destroy();
	}
	void EBO::init(const void* pData, uint32_t pCount)
	{
		mCount = pCount;
		glGenBuffers(1, &mEBOid);
		glBindBuffer(GL_INDEX_ARRAY, mEBOid);
		glBufferData(GL_INDEX_ARRAY, pCount * sizeof(uint32_t), pData, GL_STATIC_DRAW);
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