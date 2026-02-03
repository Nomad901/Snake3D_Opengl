#pragma once

#include "Engine/Model/Buffers/VAO.h"
#include "Engine/Model/Buffers/VBO.h"
#include "Engine/Model/Buffers/EBO.h"
#include "Engine/Model/Mesh/Texture.h"

namespace SnakeEngine
{
	class Mesh
	{
	public:
		Mesh() = default;
		virtual ~Mesh() = default;
		Mesh(const Mesh&) = delete;
		Mesh operator=(const Mesh&) = delete;

		virtual void draw() = 0;
		void destroy();

	protected:
		VAO mVAO;
		EBO mEBO;

		std::vector<uint32_t> mIndices;
		std::vector<SnakeEngine::Texture> mTextures;
	};
}