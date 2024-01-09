#include "pch.h"

#include "CollisionsUtils.h"
#include "Engine/Utils/TransformUtils.h"
#include <glm/mat4x4.hpp>

bool MyEngine::CollisionsUtils::AABBAABB_Overlap(const glm::vec3& minA, const glm::vec3& maxA,
												 const glm::vec3& positionA, const float& scaleA,
												 const glm::vec3& minB, const glm::vec3& maxB, 
												 const glm::vec3& positionB, const float& scaleB)
{
	// Calc transformations
	glm::mat4 matTransfA = glm::mat4(1.0f);
	TransformUtils::GetTransform(positionA, scaleA, matTransfA);

	glm::mat4 matTransfB = glm::mat4(1.0f);
	TransformUtils::GetTransform(positionB, scaleB, matTransfB);

	// Transform A in world space
	glm::vec4 AminWorld = (matTransfA * glm::vec4(minA, 1.0f));
	glm::vec4 AmaxWorld = (matTransfA * glm::vec4(maxA, 1.0f));

	// Transform B in world space
	glm::vec4 BminWorld = (matTransfB * glm::vec4(minB, 1.0f));
	glm::vec4 BmaxWorld = (matTransfB * glm::vec4(minB, 1.0f));

	// Check if objects collide
	if (AmaxWorld[0] < BminWorld[0])
	{
		return false;
	}

	if (AminWorld[0] > BmaxWorld[0])
	{
		return false;
	}

	if (AmaxWorld[1] < BminWorld[1])
	{
		return false;
	}

	if (AminWorld[1] > BmaxWorld[1])
	{
		return false;
	}

	if (AmaxWorld[2] < BminWorld[2])
	{
		return false;
	}

	if (AminWorld[2] > BmaxWorld[2])
	{
		return false;
	}

	return true;
}

bool MyEngine::CollisionsUtils::SphereAABB_Overlap(const float& radiusA, 
												   const glm::vec3& positionA, const float& scaleA, 
												   const glm::vec3& minB, const glm::vec3& maxB, 
												   const glm::vec3& positionB, const float& scaleB)
{
	float sphereRadius = radiusA * scaleA;

	// Calc transformations
	glm::mat4 matTransfB = glm::mat4(1.0f);
	TransformUtils::GetTransform(positionA, scaleB, matTransfB);

	// Transform A in world space
	glm::vec4 BminWorld = (matTransfB * glm::vec4(minB, 1.0f));
	glm::vec4 BmaxWorld = (matTransfB * glm::vec4(maxB, 1.0f));

	// Calculate the closest point on the AABB to the sphere center
	glm::vec3 closestPoint = glm::clamp(positionA, glm::vec3(BminWorld), glm::vec3(BmaxWorld));

	// Calculate the distance between the sphere center and the closest point on the AABB
	glm::vec3 offset = positionA - closestPoint;
	float distanceSquared = glm::dot(offset, offset);

	// Check if the distance is less than the squared sphere radius
	if (distanceSquared > sphereRadius * sphereRadius)
	{
		// Not hit
		return false;
	}
	return true;
}

bool MyEngine::CollisionsUtils::SphereSphere_Overlap(const float& radiusA, 
													 const glm::vec3& positionA, 
													 const float& scaleA, 
													 const float& radiusB, 
													 const glm::vec3& positionB,
													 const float& scaleB)
{
	// Calculate squared distance between centers
	glm::vec3 d = positionA - positionB;
	float dist2 = glm::dot(d, d);
	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = (radiusA * scaleA) + (radiusB * scaleB);
	if (dist2 > radiusSum * radiusSum)
	{
		// Not hit
		return false;
	}
	return true;
}
