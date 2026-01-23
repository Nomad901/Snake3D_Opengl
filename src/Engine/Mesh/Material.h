#pragma once

#include "glm/glm.hpp"
#include "Engine/Mesh/Texture.h"

namespace SnakeEngine
{
	struct Material
	{
		glm::vec4 baseColor;
		SnakeEngine::Texture texture;
		float roughness;
		float metallic;
	};
}