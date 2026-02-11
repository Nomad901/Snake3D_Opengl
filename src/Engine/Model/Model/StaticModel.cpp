#include "snkpch.h"
#include "Engine/Model/Model/StaticModel.h"
#include "Engine/Model/Mesh/Material.h"

namespace SnakeEngine
{
	void StaticModel::loadModel(const std::filesystem::path& pPath, 
								const SnakeEngine::Transform& pTransform)
	{
		mModelPath = pPath;
		mTransform = pTransform;

		init();
	}

	const std::vector<SnakeEngine::Mesh>& StaticModel::getMesh() const noexcept
	{
		return mMeshes2;
	}

	const std::vector<SnakeEngine::Material>& StaticModel::getMaterial() const noexcept
	{
		return mMaterials;
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
		mMeshes.resize(mScene->mNumMeshes);
		mMaterials.resize(mScene->mNumMaterials);

		auto numberVerticesAndIndices = getNumVerticesAndIndices();
		uint32_t numVertices = numberVerticesAndIndices.first;
		uint32_t numIndices = numberVerticesAndIndices.second;

		mVertices.reserve(numVertices);
		mIndices.reserve(numIndices);
		
		//initAllMeshes();
		//initMaterials();
		//populateBuffers();
	}

	std::pair<uint32_t, uint32_t> StaticModel::getNumVerticesAndIndices()
	{
		uint32_t numVertices = 0, numIndices = 0;
		for (size_t i = 0; i < mScene->mNumMeshes; ++i)
		{
			mMeshes[i].mNumIndices = mScene->mMeshes[i]->mFaces[i].mNumIndices;
			mMeshes[i].mBaseIndex = numIndices;
			mMeshes[i].mBaseVertex = numVertices;
			mMeshes[i].mMaterialIndex = mScene->mMeshes[i]->mMaterialIndex;

			numVertices += mScene->mMeshes[i]->mNumVertices;
			numIndices += mScene->mMeshes[i]->mFaces->mNumIndices;
		}
		return std::make_pair(numVertices, numIndices);
	}

	void StaticModel::initAllMeshes()
	{
		for (int32_t i = 0; i < mScene->mNumMeshes; ++i)
		{
			const aiMesh* mesh = mScene->mMeshes[i];
			initSingleMesh(mesh);
		}
	}
	void StaticModel::initSingleMesh(const aiMesh* pMesh)
	{
		glm::vec3 zeroVec = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 vertexPos, vertexNormals;
		glm::vec2 vertexUV;
		mVertices.reserve(pMesh->mNumVertices);

		for (uint32_t i = 0; i < pMesh->mNumVertices; ++i)
		{
			const aiVector3D& pos = pMesh->mVertices[i];
			vertexPos = glm::vec3(pos.x, pos.y, pos.z);

			const aiVector3D& normals = pMesh->mNormals ? pMesh->mNormals[i] : aiVector3D(0.0f, 1.0f, 0.0f);
			vertexNormals = glm::vec3(normals.x, normals.y, normals.z);

			const aiVector3D& UV = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][i] : aiVector3D(0.0f, 0.0f, 0.0f);
			vertexUV = glm::vec2(UV.x, UV.y);

			mVertices.push_back({vertexPos, vertexNormals, vertexUV});
		}

		for (uint32_t i = 0; i < pMesh->mNumFaces; ++i)
		{
			const aiFace& face = pMesh->mFaces[i];

			mIndices.push_back(face.mIndices[0]);
			mIndices.push_back(face.mIndices[1]);
			mIndices.push_back(face.mIndices[2]);
		}
	}
}
