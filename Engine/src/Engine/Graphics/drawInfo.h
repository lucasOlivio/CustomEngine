#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

struct sVertex
{
	float x, y, z, w;
	float r, g, b, a;
	float nx, ny, nz, nw;
	float u, v;
};

struct sTriangleMesh
{
	glm::vec3 vertices[3];

	glm::vec3 GetNormal(void)
	{
		glm::vec3 v0_1 = vertices[1] - vertices[0];
		glm::vec3 v0_2 = vertices[2] - vertices[1];

		return glm::normalize(glm::cross(v0_1, v0_2));
	}
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
	sTriangleMesh* pTriangles;

	// Mesh info
	float maxX, maxY, maxZ;
	float minX, minY, minZ;
};