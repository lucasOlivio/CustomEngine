#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	class SteeringBehaviorSystem : public iSystem
	{
	public:
		SteeringBehaviorSystem() = default;
		virtual ~SteeringBehaviorSystem() { };

		virtual std::string SystemName() { return "SteeringBehaviorSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
