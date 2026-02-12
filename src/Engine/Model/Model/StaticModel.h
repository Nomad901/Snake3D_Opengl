#pragma once

#include "Engine/Model/Model/Model.h"
#include "Engine/Model/Mesh/StaticMesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace SnakeEngine
{
	class StaticModel : public Model
	{
	public:
		StaticModel() = default;

		void loadModel(const std::filesystem::path& pPath,
					   const SnakeEngine::Transform& pTransform);

		const std::vector<SnakeEngine::Mesh>& getMesh() const noexcept override;
		const std::vector<SnakeEngine::Material>& getMaterial() const noexcept override;
		const SnakeEngine::Transform& getTransform() const noexcept override;

		void render();

	private:
		void init();
		void initFromSceneAssimp();

		std::pair<uint32_t, uint32_t> getNumVerticesAndIndices();

		void initAllMeshes();
		void initSingleMesh(const aiMesh* pMesh);

		void initMaterials();
		void loadTextures(const std::filesystem::path& pPath, const aiMaterial* pMaterial, uint32_t pIndex);
		void loadColors(const aiMaterial* pMaterial, uint32_t pIndex);

		void populateBuffers();

	private:

		enum class BUFFER_TYPE : uint32_t
		{
			INDEX_BUFFER = 0,
			POS_BUFFER = 1,
			TEXTURE_BUFFER = 2,
			NORMAL_BUFFER = 3,
			NUMBER_OF_BUFFERS = 4
		};
					
	private:
		std::filesystem::path mModelPath;

		VAO mVAO;
		EBO mEBO;
		std::array<VBO, static_cast<uint32_t>(BUFFER_TYPE::NUMBER_OF_BUFFERS)> mBuffers;

		glm::mat4 mGlobalInverseTransf;

		std::vector<SnakeEngine::StaticMesh> mMeshes;
		std::vector<SnakeEngine::BasicMeshEntry> mMeshesEntry;
		std::vector<SnakeEngine::Material> mMaterials;
		
		SnakeEngine::VertexSOA mVertices;
		std::vector<uint32_t> mIndices;

		Assimp::Importer mImporter;
		const aiScene* mScene{ nullptr };
	};
}