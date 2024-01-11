#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	// Should be the only one to change the transform component data
	class MovementSystem : public iSystem
	{
	public:
		MovementSystem() = default;
		virtual ~MovementSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
