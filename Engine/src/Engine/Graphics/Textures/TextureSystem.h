#pragma once

#include "Engine/ECS/iSystem.h"

namespace MyEngine
{
	class TextureSystem : public iSystem
	{
	public:
		TextureSystem() = default;
		virtual ~TextureSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);
	};
}
