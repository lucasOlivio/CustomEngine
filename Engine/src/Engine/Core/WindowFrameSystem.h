#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	// Keeps track of all related to FPS
	class WindowFrameSystem : public iSystem
	{
	public:
		WindowFrameSystem() = default;
		virtual ~WindowFrameSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
