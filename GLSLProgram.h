#pragma once
#include "glm.hpp"

namespace Engine
{
	class GLSLProgram
	{
	public:
		GLSLProgram();

		void CompileShaders(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
		void LinkShader();

		void AddAttribute(const char* attribName);

		uint GetUniformLocation(const char* uniformName);
		void UploadUniform(const char* uniformName, int val);
		void UploadUniform(const char* uniformName, const glm::mat4 &projectionMatrix);

		void Use();
		void UnUse();
	private:
		void compileShader(const char* filePath, uint id);

		uint m_numAtrtrib;
		uint m_programId;

		uint m_vertexShaderId;
		uint m_fragmentShaderId;
	};
}

