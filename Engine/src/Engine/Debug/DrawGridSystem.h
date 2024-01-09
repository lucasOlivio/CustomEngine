#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	// Draw the whole AABB grid from broadphase
	class DrawGridSystem : public iSystem
	{
	public:
		DrawGridSystem() = default;
		virtual ~DrawGridSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
