#pragma once

namespace Engine
{
	class GLSLProgram
	{
	public:
		GLSLProgram(void);
		~GLSLProgram(void);

		void CompileShaders(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

		void LinkShader();

		void AddAttribute(const char* attribName);

		int GLSLProgram::GetUniformLocation( const char* uniformName);

		void Use();
		void UnUse();
	private:
		void compileShader(const char* filePath, uint id);

		int numAtrtrib;
		uint programId;

		uint vertexShaderId;
		uint fragmentShaderId;
	};
}

