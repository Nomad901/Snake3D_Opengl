#pragma once

namespace SnakeEngine
{
	class EBO
	{
	public:
		EBO() = default;
		~EBO();
		EBO(const EBO&) = delete;
		EBO operator=(const EBO&) = delete;

		void init(const void* pData, uint32_t pCount);

		void destroy();
		void bind();
		void unbind();

		uint32_t getCount() const noexcept;
		uint32_t getEBOid() const noexcept;

	private:
		uint32_t mEBOid{};
		uint32_t mCount{};
	};
}