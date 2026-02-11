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

		void initMaterial();
		
		std::pair<uint32_t, uint32_t> getNumVerticesAndIndices();

		void initAllMeshes();
		void initSingleMesh(const aiMesh* pMesh);

		void initMaterials();
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