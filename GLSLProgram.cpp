#include "BaseTypes.h"
#include "GLSLProgram.h"

#include <fstream>
#include <string>
#include <vector>

#include "glew.h"
#include "Errors.h"
#include "Logger.h"

namespace Engine
{
	GLSLProgram::GLSLProgram(void) :
		m_numAtrtrib(0), m_programId(0), m_vertexShaderId(0), m_fragmentShaderId(0)
	{
	}

	void GLSLProgram::CompileShaders(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
	{
		m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		if (!m_vertexShaderId)
			fatalError("Vertex shader failed to be created!");

		m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		if (!m_fragmentShaderId)
			fatalError("Fragment shader failed to be created!");

		compileShader(vertexShaderFilePath, m_vertexShaderId);
		compileShader(fragmentShaderFilePath, m_fragmentShaderId);

		//Vertex and fragment shaders are successfully compiled.
		//Get a program object.
		m_programId = glCreateProgram();
	}

	void GLSLProgram::LinkShader()
	{
		//Attach our shaders to our program
		glAttachShader(m_programId, m_vertexShaderId);
		glAttachShader(m_programId, m_fragmentShaderId);

		//Link our program
		glLinkProgram(m_programId);

		//Note the different functions here: glGetProgram* instead of glGetShader*.
		int isLinked = 0;
		glGetProgramiv(m_programId, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::string errorLog;
			errorLog.resize(maxLength);
			glGetProgramInfoLog(m_programId, maxLength, &maxLength, &errorLog[0]);

			//We don't need the program anymore.
			glDeleteProgram(m_programId);
			//Don't leak shaders either.
			glDeleteShader(m_vertexShaderId);
			glDeleteShader(m_fragmentShaderId);

			log("%s\n", errorLog);
			fatalError("Shader faild to link");

			//In this simple program, we'll just leave
			return;
		}

		//Always detach shaders after a successful link.
		glDetachShader(m_programId, m_vertexShaderId);
		glDetachShader(m_programId, m_fragmentShaderId);
		glDeleteShader(m_vertexShaderId);
		glDeleteShader(m_fragmentShaderId);
	}

	void GLSLProgram::AddAttribute(const char* attribName)
	{
		glBindAttribLocation(m_programId, m_numAtrtrib++, attribName);
	}

	uint GLSLProgram::GetUniformLocation(const char* uniformName)
	{
		uint location = glGetUniformLocation(m_programId, uniformName);
		if (location == GL_INVALID_INDEX)
			fatalError(std::string("Uniform \"") + uniformName + "\" not found in shader");
		return location;
	}

	void GLSLProgram::Use()
	{
		glUseProgram(m_programId);
		for (uint i = 0; i < m_numAtrtrib; i++)
			glEnableVertexAttribArray(i);
	}
	void GLSLProgram::UnUse()
	{
		glUseProgram(0);
		for (uint i = 0; i < m_numAtrtrib; i++)
			glDisableVertexAttribArray(i);
	}

	void GLSLProgram::compileShader(const char* filePath, uint id)
	{
		std::ifstream file(filePath);
		if (file.fail())
		{
			perror(filePath);
			fatalError("Failed to open shader file");
		}

		std::string fileContents;

		fileContents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		file.close();

		const GLchar* chShaderSource = fileContents.c_str() + '\0';
		glShaderSource(id, 1, (const GLchar**)&chShaderSource, nullptr);

		glCompileShader(id);

		int isCompiled = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::string errorLog;
			errorLog.resize(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id); //Don't leak the shader.

			log("%s\n",errorLog);
			//Exit with failure.
			fatalError("Shader failed to compile!");

			return;
		}
	}
}