#pragma once

#include "Engine/Model/Mesh/Vertex.h"

namespace SnakeEngine
{
	class VBO
	{
	public:
		VBO() = default;
		~VBO();
		VBO(const VBO&) = delete;
		VBO operator=(const VBO&) = delete;

		void init(const void* pData, GLuint pSize, GLenum pUsage);
		
		void destroy();
		void bind();
		void unbind();

		uint32_t getVBOid() const noexcept;

	private:
		uint32_t mVBOid{};
	};
}