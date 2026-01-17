#include "snkpch.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Application/Log.h"

#include "glad/glad.h"

Shader::Shader(const std::filesystem::path& pVertexShaderPath, 
			   const std::filesystem::path& pFragmentShaderPath)
{
	std::string vertexSource   = parsePath(pVertexShaderPath);
	std::string fragmentSource = parsePath(pFragmentShaderPath);

	mShaderID = createShader(vertexSource, fragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(mShaderID);
}

void Shader::bind()
{
	glUseProgram(mShaderID);
}

void Shader::unbind()
{
	glUseProgram(0);
}

uint32_t Shader::getShaderID()
{
	return mShaderID;
}

void Shader::setMatrixUniform4fv(const std::string& pName, const glm::mat4& pMatrix4x4)
{
	glUniformMatrix4fv(getUniformLocation(pName), 1, GL_FALSE, &pMatrix4x4[0][0]);
}

bool Shader::doesUniformExist(const std::string& pName)
{
	if (mStorageLocations.contains(pName))
		return true;

	uint32_t locationID = glGetUniformLocation(mShaderID, pName.c_str());
	return locationID != -1;
}

uint32_t Shader::getUniformLocation(const std::string& pName)
{
	if (mStorageLocations.contains(pName))
		return mStorageLocations[pName];

	uint32_t locationID = glGetUniformLocation(mShaderID, pName.c_str());
	if (locationID == -1)
		GAME_WARN(std::format("Uniform does not exist! Name: {}", pName));
	mStorageLocations.emplace(pName, locationID);
	return locationID;
}

uint32_t Shader::createShader(const std::string& pVertexSource, const std::string& pFragmentSource)
{
	uint32_t program = glCreateProgram();
	uint32_t vertexShaderID = compileShader(GL_VERTEX_SHADER, pVertexSource);
	uint32_t fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, pVertexSource);

	glAttachShader(program, vertexShaderID);
	glAttachShader(program, fragmentShaderID);

	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vertexShaderID);
	glDetachShader(program, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return program;
}

uint32_t Shader::compileShader(uint32_t pShaderType, const std::string& pString)
{
	uint32_t shaderID = glCreateShader(pShaderType);
	const char* stringInChar = pString.c_str();
	glShaderSource(shaderID, 1, &stringInChar, nullptr);
	glCompileShader(shaderID);

	int32_t result = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int32_t length;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
		char* string = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shaderID, length, &length, string);

		GAME_ERROR(std::format("Could not compile shader! {}", pString));

		glDeleteShader(shaderID);
		return 0;
	} 

	return shaderID;
}

std::string Shader::parsePath(const std::filesystem::path& pPath)
{
	std::ifstream ifstream(pPath);
	if (!ifstream.is_open())
		GAME_ERROR(std::format("Ifstream was not opened! Path: {}", pPath.string()));

	std::string finalString, line;
	while (std::getline(ifstream, line))
	{
		finalString += line + '\n';
	}

	return finalString;
}
