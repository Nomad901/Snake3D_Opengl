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
		virtual ~Mesh() = default;
		Mesh(const Mesh&) = delete;
		Mesh operator=(const Mesh&) = delete;

		virtual void draw() = 0;
		virtual void destroy() = 0;

	protected:
		VAO mVAO;
		EBO mEBO;

		std::vector<uint32_t> mIndices;
		std::vector<Texture> mTextures;
	};

	class StaticMesh : public Mesh
	{
	public:
		void init(const std::vector<SnakeEngine::Vertex>& pVertices,
				  const std::vector<uint32_t>& pIndices,
				  const std::vector<Texture>& pTextures);

		void draw() override;
		void destroy() override;

		const std::vector<Texture>& getTextures() const noexcept;

	private:
		void loadMesh(const std::vector<SnakeEngine::Vertex>& pVertices);
	};
}