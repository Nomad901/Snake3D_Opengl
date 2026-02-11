#pragma once

#include "Engine/Model/Mesh/Mesh.h"
#include "Engine/Model/Mesh/Material.h"
#include "Engine/Model/Mesh/Transform.h"

namespace SnakeEngine
{
	class Model
	{
	public:
		Model() = default;
		virtual ~Model() = 0;

		virtual const std::vector<SnakeEngine::Mesh>& getMesh() const noexcept = 0;
		virtual const std::vector<SnakeEngine::Material>& getMaterial() const noexcept = 0;
		virtual const SnakeEngine::Transform& getTransform() const noexcept  = 0;

	protected:
		SnakeEngine::Transform mTransform;
	};
}