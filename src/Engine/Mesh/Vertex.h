#pragma once

#include "glm/glm.hpp"

namespace SnakeEngine
{
	struct Vertex
	{	
		glm::vec3 pos{ 0.0f, 0.0f, 0.0f };
		glm::vec3 normals{ 0.0f, 0.0f, 0.0f };
		glm::vec2 uv{ 0.0f, 0.0f };
		glm::vec4 color{ 0.0f, 0.0f, 0.0f, 0.0f };
	};
}