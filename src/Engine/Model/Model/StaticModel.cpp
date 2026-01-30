#include "snkpch.h"

#include "Engine/Model/Model/Model.h"
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
		return mMesh;
	}

	const SnakeEngine::Material& StaticModel::getMaterial() const noexcept
	{
		return mMaterial;
	}

	const SnakeEngine::Transform& StaticModel::getTransform() const noexcept
	{
		return mTransform;
	}
}
