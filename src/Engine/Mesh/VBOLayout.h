#pragma once

namespace SnakeEngine
{
	struct VBOLayoutComponents
	{
		uint8_t normalized;
		uint32_t type;
		uint32_t count;

		static uint32_t sizeOf(uint32_t pType)
		{
			switch (pType)
			{
			case GL_FLOAT:
				return sizeof(GL_FLOAT);
			case GL_UNSIGNED_BYTE:
				return sizeof(GL_UNSIGNED_BYTE);
			case GL_BYTE:
				return sizeof(GL_BYTE);
			case GL_UNSIGNED_INT:
				return sizeof(GL_UNSIGNED_INT);
			default:
				return sizeof(uint32_t);
			}
		}
	};

	class VBOLayout
	{
	public:
		VBOLayout() = default;

		auto pushLayout(uint32_t pType, uint32_t pCount) -> void;
		auto destroy() -> void;

		auto getComponentsOfLayout() -> std::vector<VBOLayoutComponents>&;
		auto getCount() const noexcept -> uint32_t;

	private:
		uint32_t mCount{};
		std::vector<VBOLayoutComponents> mVBOLayoutComponents;
	};
}