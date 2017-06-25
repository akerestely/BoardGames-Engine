#pragma once

namespace Engine
{
	class GLSLProgram
	{
	public:
		GLSLProgram();

		void CompileShaders(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
		void LinkShader();

		void AddAttribute(const char* attribName);

		uint GLSLProgram::GetUniformLocation(const char* uniformName);

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

