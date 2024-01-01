#pragma once

#include "Engine/Core/iSystem.h"
#include "Engine/Core/Components.h"

namespace MyEngine
{
	class RenderSystem : public iSystem
	{
	public:
		RenderSystem() = default;
		virtual ~RenderSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
