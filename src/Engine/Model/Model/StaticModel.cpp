#include "snkpch.h"
#include "Engine/Model/Model/StaticModel.h"

namespace SnakeEngine
{
	void StaticModel::loadModel(const std::filesystem::path& pPath, 
								const SnakeEngine::Transform& pTransform)
	{
		mModelPath = pPath;
		mTransform = pTransform;

		loadModel();
	}

	const SnakeEngine::Mesh& StaticModel::getMesh() const noexcept
	{
		return mStaticMesh;
	}

	const SnakeEngine::Material& StaticModel::getMaterial() const noexcept
	{
		return mMaterial;
	}

	const SnakeEngine::Transform& StaticModel::getTransform() const noexcept
	{
		return mTransform;
	}
	void StaticModel::loadModel()
	{
		const uint32_t ASSIMP_LOAD_FLAGS = (aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);
		mScene = mImporter.ReadFile(mModelPath.string(), ASSIMP_LOAD_FLAGS);

	}
}
