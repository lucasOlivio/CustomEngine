#pragma once

#include <glm/vec3.hpp>

namespace MyEngine
{
	class CollisionsUtils
	{
	public:
		static bool AABBAABB_Overlap(const glm::vec3& minA, const glm::vec3& maxA, 
									 const glm::vec3& positionA, const float& scaleA,
									 const glm::vec3& minB, const glm::vec3& maxB, 
									 const glm::vec3& positionB, const float& scaleB);

		static bool SphereAABB_Overlap(const float& radiusA, 
									   const glm::vec3& positionA, const float& scaleA,
									   const glm::vec3& minB, const glm::vec3& maxB, 
									   const glm::vec3& positionB, const float& scaleB);

		static bool SphereSphere_Overlap(const float& radiusA, 
										 const glm::vec3& positionA, const float& scaleA,
										 const float& radiusB, 
										 const glm::vec3& positionB, const float& scaleB);
	};
}
