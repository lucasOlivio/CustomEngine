#pragma once

#include "Engine/ECS/Base.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace MyEngine
{
	enum eBody
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

	struct sCollisionData
	{
		Entity entityA;
		Entity entityB;
		std::string tagA;
		std::string tagB;
		eBody bodyTypeA;
		eBody bodyTypeB;
		glm::vec3 contactPointA;
		glm::vec3 contactPointB;
		glm::vec3 collisionNormalA;
		glm::vec3 collisionNormalB;
		glm::vec3 positionA;
		glm::vec3 positionB;
		glm::vec3 velocityAtCollisionA;
		glm::vec3 velocityAtCollisionB;
	};
}
