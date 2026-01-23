#pragma once

namespace SnakeEngine
{
	struct Material
	{
		glm::vec4 baseColor;
		Texture texture;
		float roughness;
		float metallic;
	};
}