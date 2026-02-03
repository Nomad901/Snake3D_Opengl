#include "snkpch.h"
#include "Engine/Model/Mesh/Mesh.h"

namespace SnakeEngine
{
	void SnakeEngine::Mesh::destroy()
	{
		mVAO.destroy();
		mEBO.destroy();
	}
}
