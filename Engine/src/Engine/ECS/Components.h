#pragma once

#include "Base.h"
#include <glm/gtc/quaternion.hpp>

namespace MyEngine
{
	struct TagComponent
	{
		std::string name;
	};

	struct TransformComponent
	{
		glm::vec3 position;
		glm::quat orientation;
		float scale;
	};

	struct MovementComponent
	{
		glm::vec3 velocity;
		glm::vec3 acceleration;
	};

	struct ModelComponent
	{
		std::string name;
	};

	struct ColliderComponent
	{
		float radius;
	};

	// Singleton components


}
