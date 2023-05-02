#pragma once
#include <glew/glew.h> 
#include <glm/glm.hpp>
#include <string>
class Shader
{
public:
	Shader();
	~Shader();
	bool Load(const std::string& vertName, const std::string& fragName);
	// Unload when not use while not unload everything in the constructor
	//void Unload();
	void SetMatrixUniform(const char* name, const glm::mat4& matrix);

	void Enable();
	// void Disable();
	bool CompileShader(const std::string& fileName,
		GLenum shaderType,
		GLuint& outShader);
	// Tests whether shader compiled successfully
	bool IsCompiled(GLuint shader);
	// Tests whether vertex/fragment programs link
	bool IsValidProgram();

	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};

