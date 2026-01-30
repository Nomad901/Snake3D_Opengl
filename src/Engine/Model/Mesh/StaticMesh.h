#pragma once

namespace SnakeEngine
{
	class StaticMesh : public Mesh
	{
	public:
		void init(const std::vector<SnakeEngine::Vertex>& pVertices,
				  const std::vector<uint32_t>& pIndices,
				  const std::vector<Texture>& pTextures);

		void draw() override;

		const std::vector<Texture>& getTextures() const noexcept;

	private:
		void loadMesh(const std::vector<SnakeEngine::Vertex>& pVertices);
	};
}