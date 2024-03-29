#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	class LightFlickerSystem : public iSystem
	{
	public:
		LightFlickerSystem() = default;
		virtual ~LightFlickerSystem() { };

		virtual std::string SystemName() { return "LightFlickerSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
