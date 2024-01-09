#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	class CollisionSystem : public iSystem
	{
	public:
		CollisionSystem() = default;
		virtual ~CollisionSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
