#pragma once

#include "iShaderProgram.h"

#include <vector>
#include <map>

namespace MyEngine
{
	class Shader {
	public:
		Shader();
		~Shader();

		uint ID;
		std::vector<std::string> vecSource;
		bool isSourceMultiLine;
		std::string fileName;

		enum ShaderType
		{
			VERTEX_SHADER,
			FRAGMENT_SHADER,
			UNKNOWN
		};
		ShaderType shaderType;

		std::string GetShaderTypeString(void);
	};

	class ShaderProgram : public iShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();
		uint ID;	// ID from OpenGL
		std::string name;	// We give it this name

		// Returns -1 (just like OpenGL) if NOT found
		int GetUL(const char* name);
		// Returns -1 (just like OpenGL) if NOT found
		int GetAL(const char* name);
		// Look up the uniform location and save it.
		int LoadUniformLocation(const char* variableName);
		// Look up the attribute location and save it.
		bool LoadAttributeLocation(const char* variableName);

		void IsWireframe(bool isWireframe);

		// Loading uniform values
		void SetUniformFloat(const char* variableName, float value);
		void SetUniformInt(const char* variableName, int value);
		void SetUniformMatrix4f(const char* variableName, const glm::mat4& value);
		void SetUniformVec4(const char* variableName, const glm::vec4& value);
		void SetUniformVec2(const char* variableName, const glm::vec2& value);

		void BindTexture(uint textureUnit, uint textureId);
	private:
		std::map< std::string /*name of uniform variable*/,
			int /* uniform location ID */ >
			m_mapUniformNameToUniformLocation;
		std::map< std::string /*name of attribute variable*/,
			int /* attribute location ID */ >
			m_mapAttributeNameToAttributeLocation;
	};
}
