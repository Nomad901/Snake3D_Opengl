#pragma once

#include "glm/glm.hpp"
#include "Engine/Model/Mesh/Texture.h"
#include "Engine/Renderer/Shader.h"

namespace SnakeEngine
{
	struct Material
	{
		glm::vec4 baseColor;
		std::unique_ptr<SnakeEngine::Texture> diffuseTexture;
		std::unique_ptr<SnakeEngine::Texture> specularTexture;
		std::unique_ptr<SnakeEngine::Shader> shader;
		float roughness;
		float metallic;
	};
}