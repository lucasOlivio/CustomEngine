#pragma once

#include "Engine/Core/Base.h"

namespace MyEngine
{
	struct TagComponent
	{
		std::string name;
	};

	struct TransformComponent
	{
		glm::vec2 position;
		float angle;
		float scale;
	};

	struct MovementComponent
	{
		glm::vec2 velocity;
		glm::vec2 acceleration;
	};

	struct SpriteComponent
	{
		std::string name;
		int cols;
		int rows;
		float speed;
	};

	struct ColliderComponent
	{
		float radius;
	};

	// Singleton components


}
