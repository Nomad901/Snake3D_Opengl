#include "snkpch.h"
#include "Engine/Model/Model/StaticModel.h"

namespace SnakeEngine
{
	void StaticModel::loadModel(const std::filesystem::path& pPath, 
								const SnakeEngine::Transform& pTransform)
	{
		mModelPath = pPath;
		mTransform = pTransform;

		init();
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
	void StaticModel::init()
	{
		const uint32_t ASSIMP_LOAD_FLAGS = (aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);
		mScene = mImporter.ReadFile(mModelPath.string(), ASSIMP_LOAD_FLAGS);

		if (mScene)
		{
			mGlobalInverseTransf = SnakeEngine::AssimpUtils::getGlmMat4FromAiMat4x4(mScene->mRootNode->mTransformation);
			mGlobalInverseTransf = glm::inverse(mGlobalInverseTransf);
			initFromSceneAssimp();
		}
		else
			GAME_ERROR("couldnt initialize the scene in static model!");
	}
	void StaticModel::initFromSceneAssimp()
	{

	}
	void StaticModel::initMaterial()
	{
	}
}
