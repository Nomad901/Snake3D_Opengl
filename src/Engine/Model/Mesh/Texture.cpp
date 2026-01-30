#include "snkpch.h"
#include "Engine/Model/Mesh/Texture.h"
#include "Engine/Application/Log.h"

#include "stb_image.h"

namespace SnakeEngine
{
	SnakeEngine::Texture::~Texture()
	{
		glDeleteTextures(1, &mTextureID);
	}

	void SnakeEngine::Texture::init(const std::filesystem::path& pPath, GLenum pTextureTarget)
	{
		mTextureTarget = pTextureTarget;
		stbi_set_flip_vertically_on_load(1);
		int32_t width, height, bpp;
		auto localBuffer = stbi_load(pPath.string().c_str(), &width, &height, &bpp, 4);
		if (!localBuffer)
		{
			GAME_ERROR(std::format("Couldnt load the texture: {}", pPath.string()));
			return;
		}

		glGenTextures(1, &mTextureID);
		glBindTexture(pTextureTarget, mTextureID);

		glTexParameteri(pTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(pTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(pTextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(pTextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(pTextureTarget, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
		glBindTexture(pTextureTarget, 0);

		if (localBuffer)
			stbi_image_free(localBuffer);
	}

	void SnakeEngine::Texture::bind(uint32_t pSlot)
	{
		glActiveTexture(GL_TEXTURE0 + pSlot);
		glBindTexture(mTextureTarget, mTextureID);
	}

	void SnakeEngine::Texture::unbind()
	{
		glBindTexture(mTextureTarget, 0);
	}

	void Texture::setTextureType(std::string_view pTextureType)
	{
		mTextureType = pTextureType;
	}

	uint32_t SnakeEngine::Texture::getTextureID() const noexcept
	{
		return mTextureID;
	}

	GLenum SnakeEngine::Texture::getTextureTarget() const noexcept
	{
		return mTextureTarget;
	}
}