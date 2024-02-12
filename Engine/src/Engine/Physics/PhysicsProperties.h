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
		ACTIVE,
		PASSIVE
	};

	struct sCollisionData
	{
		Entity entityA;
		Entity entityB;
		glm::vec3 contactPoint;
		glm::vec3 collisionNormalA;
		glm::vec3 collisionNormalB;
		glm::vec3 velocityAtCollisionA;
		glm::vec3 velocityAtCollisionB;

		bool operator==(const sCollisionData& other) const
		{
			return entityA == other.entityA && entityB == other.entityB;
		}

		bool operator<(const sCollisionData& other) const
		{
			return entityB < other.entityB;
		}
	};

	struct SoftBodyParticle
	{
		SoftBodyParticle()
		{
			acceleration = glm::vec3(0.0f);
			velocity = glm::vec3(0.0f);
			position = glm::vec3(0.0f);

			mass = 0.0f;
		}

		glm::vec3 acceleration;
		glm::vec3 velocity;
		glm::vec3 position;

		float mass;
	};

	struct SoftBodySpring
	{
		SoftBodySpring()
		{
			restLength = 0.0f;
			strength = 0.0f;
		}

		float restLength;
		float strength;

		SoftBodyParticle* particleA;
		SoftBodyParticle* particleB;
	};
}
