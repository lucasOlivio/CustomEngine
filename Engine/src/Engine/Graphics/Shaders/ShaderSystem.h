#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	class ShaderSystem : public iSystem
	{
	public:
		ShaderSystem() = default;
		virtual ~ShaderSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
