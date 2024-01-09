#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	// Set the current FPS at the window title
	class WindowFPSSystem : public iSystem
	{
	public:
		WindowFPSSystem() = default;
		virtual ~WindowFPSSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
