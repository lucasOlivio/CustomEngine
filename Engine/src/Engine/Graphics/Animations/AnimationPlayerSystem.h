#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	// Handles the time for all animations, 
	// decoupled from animation system to allow more options on how to run the animations
	class AnimationPlayerSystem : public iSystem
	{
	public:
		AnimationPlayerSystem() = default;
		virtual ~AnimationPlayerSystem() { };

		virtual std::string SystemName() { return "AnimationPlayerSystem"; };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();
	};
}
