#pragma once

#include "glm/glm.hpp"

namespace SnakeEngine
{
	const uint32_t MAX_BONES = 4;

	struct BoneVertex
	{
		glm::vec3 pos{ 0.0f, 0.0f, 0.0f };
		glm::vec3 normals{ 0.0f, 0.0f, 0.0f };
		glm::vec2 uv{ 0.0f, 0.0f };
		
		std::array<int32_t, MAX_BONES> bones{};
		std::array<float, MAX_BONES> bonesWeight{};
	};
}