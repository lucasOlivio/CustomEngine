#pragma once

#include "Engine/ECS/System/iSystem.h"

#include "Engine/Events/SceneEvent.h"

namespace MyEngine
{
	// Side bar with selected entity and components UI
	class EntityBarSystem : public iSystem
	{
	public:
		EntityBarSystem() = default;
		virtual ~EntityBarSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
