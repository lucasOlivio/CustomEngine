#pragma once

#include "Engine/Core/Base.h"
#include "Scene.h"

namespace MyEngine
{
	class iSystem
	{
	public:
		iSystem() = default;
		virtual ~iSystem() { };

		virtual void Start(Scene* pScene) = 0;

		virtual void Update(Scene* pScene, float deltaTime) = 0;

		virtual void Render(Scene* pScene) = 0;

		virtual void End(Scene* pScene) = 0;
	};
}
