#pragma once

namespace SnakeEngine
{
	class Model
	{
	public:
		Model() = default;
		~Model();

		auto init(const std::filesystem::path& pModelPath,
				  const SnakeEngine::Transform& pTransform) -> void;

		auto getMesh() const noexcept -> const SnakeEngine::Mesh&;
		auto getMaterial() const noexcept -> const SnakeEngine::Material&;
		auto getTransform() const noexcept -> const SnakeEngine::Transform&;

	private:
		SnakeEngine::Mesh mMesh;
		SnakeEngine::Material mMaterial;
		SnakeEngine::Transform mTransform;
	};
}