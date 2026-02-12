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
		return std::vector<SnakeEngine::Mesh>();
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
		mVAO.generate();
		mVAO.bind();

		std::array<uint32_t, static_cast<uint32_t>(BUFFER_TYPE::NUMBER_OF_BUFFERS)> tmpBuffers;
		glGenBuffers(tmpBuffers.size(), tmpBuffers.data());
		for (size_t i = 0; i < tmpBuffers.size(); ++i)
		{
			mBuffers[i].setID(tmpBuffers[i]);
		}

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

		mVertices.pos.reserve(numVertices);
		mVertices.normals.reserve(numVertices);
		mVertices.uv.reserve(numVertices);
		mIndices.reserve(numIndices);
		
		initAllMeshes();
		initMaterials();
		populateBuffers();
	}

	std::pair<uint32_t, uint32_t> StaticModel::getNumVerticesAndIndices()
	{
		uint32_t numVertices = 0, numIndices = 0;
		for (size_t i = 0; i < mScene->mNumMeshes; ++i)
		{
			mMeshesEntry[i].mNumIndices = mScene->mMeshes[i]->mFaces[i].mNumIndices;
			mMeshesEntry[i].mBaseIndex = numIndices;
			mMeshesEntry[i].mBaseVertex = numVertices;
			mMeshesEntry[i].mMaterialIndex = mScene->mMeshes[i]->mMaterialIndex;

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

		for (uint32_t i = 0; i < pMesh->mNumVertices; ++i)
		{
			const aiVector3D& pos = pMesh->mVertices[i];
			mVertices.pos.push_back(glm::vec3(pos.x, pos.y, pos.z));

			const aiVector3D& normals = pMesh->mNormals ? pMesh->mNormals[i] : aiVector3D(0.0f, 1.0f, 0.0f);
			mVertices.normals.push_back(glm::vec3(normals.x, normals.y, normals.z));

			const aiVector3D& UV = pMesh->HasTextureCoords(0) ? pMesh->mTextureCoords[0][i] : aiVector3D(0.0f, 0.0f, 0.0f);
			mVertices.uv.push_back(glm::vec2(UV.x, UV.y));
		}

		for (uint32_t i = 0; i < pMesh->mNumFaces; ++i)
		{
			const aiFace& face = pMesh->mFaces[i];

			mIndices.push_back(face.mIndices[0]);
			mIndices.push_back(face.mIndices[1]);
			mIndices.push_back(face.mIndices[2]);
		}
	}

	void StaticModel::initMaterials()
	{
		std::filesystem::path directory = mModelPath.parent_path();

		for (uint32_t i = 0; i < mScene->mNumMaterials; ++i)
		{
			loadTextures(directory, mScene->mMaterials[i], i);
			loadColors(mScene->mMaterials[i], i);
		}
	}

	void StaticModel::loadTextures(const std::filesystem::path& pPath, const aiMaterial* pMaterial, uint32_t pIndex)
	{
		mMaterials[pIndex].diffuseTexture = nullptr;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		{
			aiString texturePath;
			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
			{
				std::string fullPath = pPath.string() + "/" + texturePath.data;
				mMaterials[pIndex].diffuseTexture = std::make_unique<SnakeEngine::Texture>();
				mMaterials[pIndex].diffuseTexture->init(fullPath, GL_TEXTURE_2D);
			}
		}

		mMaterials[pIndex].specularTexture = nullptr;

		if (pMaterial->GetTextureCount(aiTextureType_SHININESS) > 0)
		{
			aiString texturePath;
			if (pMaterial->GetTexture(aiTextureType_SHININESS, 0, &texturePath) == AI_SUCCESS)
			{
				std::string fullPath = pPath.string() + "/" + texturePath.data;
				mMaterials[pIndex].specularTexture = std::make_unique<SnakeEngine::Texture>();
				mMaterials[pIndex].specularTexture->init(fullPath, GL_TEXTURE_2D);
			}
		}
    }

	void StaticModel::loadColors(const aiMaterial* pMaterial, uint32_t pIndex)
	{
		aiColor4D ambientColor = aiColor4D(0.0f);
		aiColor4D diffuseColor = aiColor4D(0.0f);
		aiColor4D specularColor = aiColor4D(0.0f);

		glm::vec4 defaultAmbientColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		glm::vec4 defaultDiffuseColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
		glm::vec4 defaultSpecularColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		
		if (pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == AI_SUCCESS)
		{
			mMaterials[pIndex].ambientColor = glm::vec4(ambientColor.r,
														ambientColor.g,
														ambientColor.b, 
														1.0f);
		}
		else
		{
			mMaterials[pIndex].ambientColor = defaultAmbientColor;
		}

		if (pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS)
		{
			mMaterials[pIndex].diffuseColor = glm::vec4(diffuseColor.r,
														diffuseColor.g,
														diffuseColor.b, 
														1.0f);
		}
		else
		{
			mMaterials[pIndex].diffuseColor = defaultDiffuseColor;
		}

		if (pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS)
		{
			mMaterials[pIndex].specularColor = glm::vec4(specularColor.r,
														 specularColor.g,
														 specularColor.b, 
														 1.0f);
		}
		else
		{
			mMaterials[pIndex].specularColor = defaultSpecularColor;
		}
	}
	void StaticModel::populateBuffers()
	{
		mVAO.bind();

		uint32_t posBufferIndex = static_cast<uint32_t>(BUFFER_TYPE::POS_BUFFER);
		uint32_t normalBufferIndex = static_cast<uint32_t>(BUFFER_TYPE::INDEX_BUFFER);
		uint32_t textureBufferIndex = static_cast<uint32_t>(BUFFER_TYPE::TEXTURE_BUFFER);
		uint32_t indexBufferIndex = static_cast<uint32_t>(BUFFER_TYPE::INDEX_BUFFER);

		uint32_t posLocation = 0;
		uint32_t normalLocation = 1;
		uint32_t textureLocation = 2;
		uint32_t indicesLocation = 3;

		auto setPointer = [](uint32_t pLocation, uint32_t pStride) -> void
			{
				glEnableVertexAttribArray(pLocation);
				glVertexAttribPointer(pLocation, pStride, GL_FLOAT, GL_FALSE, 0, nullptr);
			};

		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[posBufferIndex].getVBOid());
		glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices.pos[0]) * mVertices.pos.size(), mVertices.pos.data(), GL_STATIC_DRAW);
		setPointer(posLocation, 3);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[normalBufferIndex].getVBOid());
		glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices.normals[0]) * mVertices.normals.size(), mVertices.normals.data(), GL_STATIC_DRAW);
		setPointer(normalLocation, 3);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[textureBufferIndex].getVBOid());
		glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices.uv[0]) * mVertices.uv.size(), mVertices.uv.data(), GL_STATIC_DRAW);
		setPointer(textureLocation, 2);

		glBindBuffer(GL_ARRAY_BUFFER, mBuffers[indexBufferIndex].getVBOid());
		glBufferData(GL_ARRAY_BUFFER, sizeof(mIndices[0]) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);
	}
}
