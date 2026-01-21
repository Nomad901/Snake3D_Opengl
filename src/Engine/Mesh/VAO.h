#pragma once

#include "Engine/Mesh/VBOLayout.h"

namespace SnakeEngine
{
	class VAO
	{
	public:
		VAO() = default;
		~VAO();
		VAO(const VAO&) = delete;
		VAO operator=(const VAO&) = delete;
		
		void addBuffer(VBOLayout& pVBOLayout);

		void destroy();
		void generate();
		void bind();
		void unbind();

		uint32_t getVAOid() const noexcept;
	private:
		uint32_t mVAOid;
	};
}