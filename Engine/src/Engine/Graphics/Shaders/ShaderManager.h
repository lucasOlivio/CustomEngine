#pragma once

#include "iShaderProgram.h"
#include "Engine/Core/types.h"
#include <glm/mat4x4.hpp>
#include <string>
#include <vector>
#include <map>

namespace MyEngine
{
	class ShaderManager
	{
	public:
		ShaderManager(std::string basePath);
		~ShaderManager();

		// Where we initialize all things that could go wrong
		bool AddShaderProgram(std::string shaderProgram);

		bool CreateProgramFromFile(std::string shaderProgram,
									std::string vertexName,
									std::string fragName);
		void SetBasePath(std::string basepath);

		// Clears last error
		std::string GetLastError(void);

		uint GetIDFromShaderProgramName(std::string& shaderProgram);

		// Used to load the uniforms. Returns NULL if not found.
		iShaderProgram* GetShaderProgramFromName(std::string& shaderProgram);
		iShaderProgram* GetShaderProgramFromID(uint shaderProgramID);

		static iShaderProgram* GetActiveShader();

		// Bind opengl to this shader program
		bool UseShaderProgram(uint ID);
		bool UseShaderProgram(std::string& shaderProgram);

	private:
		// Returns an empty string if it didn't work
		bool m_LoadSourceFromFile(std::string filename, 
								  std::vector<std::string>& vecSource, 
								  std::string& errorText);

		bool m_CompileShaderFromSource(uint shaderId,
									   std::vector<std::string>& vecSource, 
									   std::string& error);
		// returns false if no error
		bool m_WasThereACompileError(uint shaderID, std::string& errorText);
		bool m_WasThereALinkError(uint progID, std::string& errorText);

		std::string m_basepath;

		std::string m_lastError;

		static iShaderProgram* m_pActiveShader;

		std::map< uint /*ID*/, iShaderProgram* > m_IDToShaderProgram;
		std::map< std::string /*name*/, uint /*ID*/ > m_shaderProgramNameToID;
	};
}