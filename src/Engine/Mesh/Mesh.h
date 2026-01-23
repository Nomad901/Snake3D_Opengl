#pragma once

#include "Engine/Mesh/VAO.h"
#include "Engine/Mesh/VBO.h"
#include "Engine/Mesh/EBO.h"

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

	private:
		VAO mVAO;
		EBO mEBO;
	};
}