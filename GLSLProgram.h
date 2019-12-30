#pragma once
#include "glm.hpp"

#include <cstdint>

namespace Engine
{
	class GLSLProgram
	{
	public:
		GLSLProgram();

		void CompileShaders(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
		void LinkShader();

		void AddAttribute(const char* attribName);

		uint32_t GetUniformLocation(const char* uniformName);
		void UploadUniform(const char* uniformName, int val);
		void UploadUniform(const char* uniformName, const glm::mat4 &projectionMatrix);

		void Use();
		void UnUse();
	private:
		void compileShader(const char* filePath, uint32_t id);

		uint32_t m_numAtrtrib;
		uint32_t m_programId;

		uint32_t m_vertexShaderId;
		uint32_t m_fragmentShaderId;
	};
}

