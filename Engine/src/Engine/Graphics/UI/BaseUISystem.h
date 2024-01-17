#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	// Manages the ImGui per frame and its initialization, should be placed after any interface system to render
	class BaseUISystem : public iSystem
	{
	public:
		BaseUISystem() = default;
		virtual ~BaseUISystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
