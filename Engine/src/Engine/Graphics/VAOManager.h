#pragma once

#include "drawinfo.h"
#include <string>
#include <map>

namespace MyEngine
{
	class VAOManager
	{
	public:
		VAOManager();
		~VAOManager();

		void DestroyVBO(std::string modelName);

		sMesh* LoadModelIntoVAO(std::string& fileName, bool bIsDynamicBuffer,
								bool hasNormals, bool hasTexture);
		// Normals and texture as default
		sMesh* LoadModelIntoVAO(std::string& fileName, bool bIsDynamicBuffer);

		bool UpdateVAOBuffers(std::string& fileName,
			std::string& shaderProgram,
			sMesh* pUpdatedMesh);

		sMesh* FindMeshByModelName(std::string& filename);

		void SetBasePath(std::string basePath);
	private:
		std::string m_basePath;
		std::map< std::string    /*model name*/,
			sMesh* /* info needed to draw*/ >
			m_mapModelNameToMesh;

		bool m_LoadMeshData(std::string theFileName, sMesh* drawInfo);
	};
}

