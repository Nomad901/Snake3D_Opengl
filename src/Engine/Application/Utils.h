#pragma once

#include "assimp/Importer.hpp"

namespace SnakeEngine
{
	struct AssimpUtils
	{
		static glm::mat4 getGlmMat4FromAiMat4x4(const aiMatrix4x4 pAiMatrix4x4)
		{
			glm::mat4 glmMatrix = glm::mat4(pAiMatrix4x4.a1, pAiMatrix4x4.a2, pAiMatrix4x4.a3, pAiMatrix4x4.a4,
											pAiMatrix4x4.b1, pAiMatrix4x4.b2, pAiMatrix4x4.b3, pAiMatrix4x4.b4,
											pAiMatrix4x4.c1, pAiMatrix4x4.c2, pAiMatrix4x4.c3, pAiMatrix4x4.c4,
											pAiMatrix4x4.d1, pAiMatrix4x4.d2, pAiMatrix4x4.d3, pAiMatrix4x4.d4);
			return glm::transpose(glmMatrix);
		}
		static aiMatrix4x4 getAiMat4x4FromGlmMat4(const glm::mat4& pMatrix)
		{
			return aiMatrix4x4(ai_real(pMatrix[0][0]), ai_real(pMatrix[0][1]), ai_real(pMatrix[0][2]), ai_real(pMatrix[0][3]),
							   ai_real(pMatrix[1][0]), ai_real(pMatrix[1][1]), ai_real(pMatrix[1][2]), ai_real(pMatrix[1][3]),
							   ai_real(pMatrix[2][0]), ai_real(pMatrix[2][1]), ai_real(pMatrix[2][2]), ai_real(pMatrix[2][3]),
							   ai_real(pMatrix[3][0]), ai_real(pMatrix[3][1]), ai_real(pMatrix[3][2]), ai_real(pMatrix[3][3]));
		}
	};
}
