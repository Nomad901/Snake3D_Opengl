#pragma once

#include "Engine/Model/Mesh/Mesh.h"
#include "Engine/Model/Mesh/BoneVertex.h"

namespace SnakeEngine
{
	class DynamicMesh : public Mesh
	{
	public:
		void init(const std::vector<SnakeEngine::BoneVertex>& pVertices,
				  const std::vector<uint32_t>& pIndices,
				  std::vector<SnakeEngine::Texture>& pTextures);

		void draw() override;

		std::vector<SnakeEngine::Texture>& getTextures() noexcept;
		
	private:
		void loadMesh(const std::vector<SnakeEngine::BoneVertex>& pVertices);
	};
}