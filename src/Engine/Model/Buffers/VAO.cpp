#include "snkpch.h"
#include "Engine/Model/Buffers/VAO.h"

namespace SnakeEngine
{
	VAO::~VAO()
	{
		destroy();
	}
	void VAO::addBuffer(VBOLayout& pVBOLayout)
	{
		bind();
		auto& elements = pVBOLayout.getComponentsOfLayout();
		uint32_t stride = 0;
		for (size_t i = 0; i < elements.size(); ++i)
		{
			auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count, element.type, element.normalized, pVBOLayout.getCount(), (void*)stride);
			stride += element.count * VBOLayoutComponents::sizeOf(element.type);
		}
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
