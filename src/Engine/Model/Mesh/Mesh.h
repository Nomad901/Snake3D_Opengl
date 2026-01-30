#pragma once

#include "Engine/Model/Buffers/VAO.h"
#include "Engine/Model/Buffers/VBO.h"
#include "Engine/Model/Buffers/EBO.h"

namespace SnakeEngine
{
	class Mesh
	{
	public:
		Mesh() = default;
		~Mesh() = default;
		Mesh(const Mesh&) = delete;
		Mesh operator=(const Mesh&) = delete;

		void init(const std::vector<SnakeEngine::Vertex>& pVertices,
				  const std::vector<uint32_t>& pIndices);
		void draw();
		void destroy();

	private:
		VAO mVAO;
		EBO mEBO;
	};
}