#pragma once

namespace SnakeEngine
{
	class Model
	{
	public:
		Model() = default;
		~Model();

		void init(const std::filesystem::path& pModelPath);

		const SnakeEngine::Mesh& getMesh() const noexcept;
		const SnakeEngine::Material& getMaterial() const noexcept;

	private:
		SnakeEngine::Mesh mMesh;
		SnakeEngine::Material mMaterial;
	};
}