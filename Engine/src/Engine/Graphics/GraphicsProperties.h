#pragma once

#include "Engine/Core/Shapes.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace MyEngine
{
	struct sVertex
	{
		float x, y, z, w;
		float r, g, b, a;
		float nx, ny, nz, nw;
		float u, v;
	};

	struct sMesh
	{
		~sMesh()
		{
			delete[] pIndices;
			delete[] pTriangles;
			delete[] pVertices;
		}

		glm::vec3 GetExtent()
		{
			return glm::vec3(
				maxX - minX,
				maxY - minY,
				maxZ - minZ
			);
		}

		std::string name;

		unsigned int VAO_ID;

		unsigned int vertexBufferID;
		unsigned int vertexBuffer_Start_Index;
		unsigned int numberOfVertices;

		unsigned int indexBufferID;
		unsigned int indexBuffer_Start_Index;
		unsigned int numberOfIndices;
		unsigned int numberOfTriangles;

		// The index buffer (CPU side)
		unsigned int* pIndices;
		sVertex* pVertices;
		sTriangle* pTriangles;

		// Mesh info
		float maxX, maxY, maxZ;
		float minX, minY, minZ;
	};

	struct sMaterialInfo
	{
		std::string name = "";
		std::string alphaTexture = "";
		std::string cubeTexture = "";
		std::string discardTexture = "";
		std::string specularTexture = "";
		std::string normalTexture = "";
		std::string heightMapTexture = "";
		std::vector<std::string> colorTextures = {};

		glm::vec3 offset = glm::vec3(0.0f); // fixed offset

		glm::vec3 currOffset = glm::vec3(0.0f);
		glm::vec3 offsetMove = glm::vec3(0.0f);

		glm::vec3 currOffsetHeightMap = glm::vec3(0.0f);
		glm::vec3 offsetHeightMap = glm::vec3(0.0f);

		glm::vec3 colorTexturesRatios = glm::vec3(0.0f);

		float heightScale = 0.0f;

		bool useHeightMap = false;
		bool useNormalTexture = false;
		bool useSpecularTexture = false;
		bool useDiscardTexture = false;
		bool useCubeTexture = false;
		bool isEmissive = false;
		bool useAlphaTexture = false;
	};

	struct sRenderModelInfo
	{
		std::string materialName = "";
		
		glm::mat4 matModel = glm::mat4(1.0f);
		glm::vec4 debugColor = glm::vec4(1.0f);
		glm::vec3 defaultColor = glm::vec3(1.0f);
		glm::vec3 tileAxis = glm::vec3(1.0f);
		glm::vec3 tileOffset = glm::vec3(0.0f);

		int VAO_ID = 0;
		int numberOfIndices = 0;

		bool isWireFrame = false;
		bool doNotLight = false;
		bool useDefaultColor = false;
		bool useColorTexture = false;
		bool useDebugColor = false;
	};
}
