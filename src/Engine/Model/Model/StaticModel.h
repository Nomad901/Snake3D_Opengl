#pragma once

namespace SnakeEngine
{
	class StaticModel : public Model
	{
	public:
		StaticModel() = default;

		void loadModel(const std::filesystem::path& pPath,
					   const SnakeEngine::Transform& pTransform);
		
		const SnakeEngine::Mesh& getMesh() const noexcept override;
		const SnakeEngine::Material& getMaterial() const noexcept override;
		const SnakeEngine::Transform& getTransform() const noexcept override;

	private:
		void loadModel();
		void initMaterial();

	private:
		std::filesystem::path mModelPath;

		SnakeEngine::Material mMaterial;
		SnakeEngine::Mesh mMesh;
	};
}