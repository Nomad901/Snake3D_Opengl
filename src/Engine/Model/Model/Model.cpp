#include "snkpch.h"
#include "Engine/Model/Model/Model.h"
#include "Engine/Model/FormatLoaders/OBJLoader.h"

namespace SnakeEngine
{
    auto Model::init(const std::filesystem::path& pModelPath, 
                     const SnakeEngine::Transform& pTransform) -> void
    {
        if (pModelPath.extension() == ".obj")
        {
            mVertices = SnakeEngine::loadOBJ(pModelPath);
            std::vector<uint32_t> indices(mVertices.size() * 6);
            
            for (size_t i = 0; i < indices.size(); i += 6)
            {
                indices[i] = i;
            }

            mMesh.init(mVertices, indices);
        }

        mTransform = pTransform;
    }
    auto Model::getMesh() const noexcept -> const SnakeEngine::Mesh&
    {
        return mMesh;
    }
    auto Model::getMaterial() const noexcept -> const SnakeEngine::Material&
    {
        return mMaterial;
    }
    auto Model::getTransform() const noexcept -> const SnakeEngine::Transform&
    {
        return mTransform;
    }
}