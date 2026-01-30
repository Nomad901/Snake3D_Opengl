#pragma once

namespace SnakeEngine
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture();
		Texture(const Texture&) = delete;
		Texture operator=(const Texture&) = delete;

		void init(const std::filesystem::path& pPath, GLenum pTextureTarget);

		void bind(uint32_t pSlot = 0);
		void unbind();

		void setTextureName(std::string_view pTextureName);

		uint32_t getTextureID() const noexcept;
		GLenum getTextureTarget() const noexcept;

	private:
		uint32_t mTextureID{};
		GLenum mTextureTarget;

		std::string mTextureName;
	};
}

