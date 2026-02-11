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

	private:
		void init();
		void initFromSceneAssimp();

		std::pair<uint32_t, uint32_t> getNumVerticesAndIndices();

		void initAllMeshes();
		void initSingleMesh(const aiMesh* pMesh);

		void initMaterials();
		void loadTextures(const std::filesystem::path& pPath, const aiMaterial* pMaterial, uint32_t pIndex);
		void loadColors(const aiMaterial* pMaterial, uint32_t pIndex);

		void populateBuffer();
		void populateBuffers();

	private:
		std::filesystem::path mModelPath;

		glm::mat4 mGlobalInverseTransf;

		std::vector<SnakeEngine::Mesh> mMeshes2;
		std::vector<SnakeEngine::BasicMeshEntry> mMeshes;
		std::vector<SnakeEngine::Material> mMaterials;
		
		std::vector<SnakeEngine::Vertex> mVertices;
		std::vector<uint32_t> mIndices;

		Assimp::Importer mImporter;
		const aiScene* mScene{ nullptr };
	};
}