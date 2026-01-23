#include "snkpch.h"
#include "Texture.h"

SnakeEngine::Texture::~Texture()
{
}

void SnakeEngine::Texture::init(const std::filesystem::path& pPath, GLenum pTextureTarget)
{
}

void SnakeEngine::Texture::bind(uint32_t pSlot)
{
}

void SnakeEngine::Texture::unbind()
{
}

uint32_t SnakeEngine::Texture::getTextureID() const noexcept
{
	return 0;
}

GLenum SnakeEngine::Texture::getTextureTarget() const noexcept
{
	return GLenum();
}
