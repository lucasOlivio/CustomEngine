#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	class LightFlickerSystem : public iSystem
	{
	public:
		LightFlickerSystem() = default;
		virtual ~LightFlickerSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
