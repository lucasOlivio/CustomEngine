#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	// Initializes debug objects
	class DebugSystem : public iSystem
	{
	public:
		DebugSystem() = default;
		virtual ~DebugSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
