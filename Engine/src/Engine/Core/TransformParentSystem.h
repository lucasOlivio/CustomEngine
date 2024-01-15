#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	// Keeps the world values from transform updated relative to parent
	class TransformParentSystem : public iSystem
	{
	public:
		TransformParentSystem() = default;
		virtual ~TransformParentSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
