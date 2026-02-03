#pragma once

#include "Engine/Model/Mesh/Mesh.h"

namespace SnakeEngine
{
	class StaticMesh : public Mesh
	{
	public:
		void init(const std::vector<SnakeEngine::Vertex>& pVertices,
				  const std::vector<uint32_t>& pIndices,
				  std::vector<SnakeEngine::Texture>& pTextures);

		void draw() override;

		std::vector<SnakeEngine::Texture>& getTextures() noexcept;

	private:
		void loadMesh(const std::vector<SnakeEngine::Vertex>& pVertices);
	};
}