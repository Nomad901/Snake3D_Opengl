#include "snkpch.h"
#include "Engine/Mesh/VBOLayout.h"

namespace SnakeEngine
{
	auto SnakeEngine::VBOLayout::pushLayout(uint32_t pType, uint32_t pCount) -> void
	{
		VBOLayoutComponents components;
		components.count = pCount;
		components.type = pType;
		components.normalized = GL_FALSE;

		mVBOLayoutComponents.push_back(components);
		mCount += pCount * VBOLayoutComponents::sizeOf(pType);
	}

	auto SnakeEngine::VBOLayout::destroy() -> void
	{
		mCount = 0;
		mVBOLayoutComponents.clear();
	}

	auto SnakeEngine::VBOLayout::getComponentsOfLayout() -> std::vector<VBOLayoutComponents>&
	{
		return mVBOLayoutComponents;
	}

	auto SnakeEngine::VBOLayout::getCount() const noexcept -> uint32_t
	{
		return mCount;
	}
}