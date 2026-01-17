#pragma once
#include <filesystem>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader
{
public:
	Shader(const std::filesystem::path& pVertexShaderPath,
		   const std::filesystem::path& pFragmentShaderPath);
	~Shader();

	void bind();
	void unbind();

	uint32_t getShaderID();

	void setMatrixUniform4fv(const std::string& pName, const glm::mat4& pMatrix4x4);

	bool doesUniformExist(const std::string& pName);
	uint32_t getUniformLocation(const std::string& pName);

private:
	uint32_t createShader(const std::string& pVertexSource, const std::string& pFragmentSource);
	uint32_t compileShader(uint32_t pShaderType, const std::string& pString);
	std::string parsePath(const std::filesystem::path& pPath);

private:
	uint32_t mShaderID{};

	std::unordered_map<std::string, uint32_t> mStorageLocations;
};

