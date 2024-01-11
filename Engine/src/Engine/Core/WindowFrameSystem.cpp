#include "pch.h"

#include "WindowFrameSystem.h"
#include "Engine/ECS/SingletonComponents/WindowLocator.h"
#include "Engine/ECS/SingletonComponents/FrameCounterLocator.h"

namespace MyEngine
{
	void WindowFrameSystem::Start(Scene* pScene)
	{
	}

	void WindowFrameSystem::Update(Scene* pScene, float deltaTime)
	{
		FrameCounterComponent* pFrame = FrameCounterLocator::Get();

		pFrame->frameCount++;

		pFrame->fpsTimer += deltaTime;

		// Update Frame every second in the title
		if (pFrame->fpsTimer >= 1.0f)
		{
			pFrame->fps = (float)(pFrame->frameCount) / pFrame->fpsTimer;

			// Update window name
			WindowComponent* pWindow = WindowLocator::Get();
			pWindow->name = std::to_string(pFrame->fps);

			pFrame->frameCount = 0;
			pFrame->fpsTimer = 0.0f;
		}
	}

	void WindowFrameSystem::Render(Scene* pScene)
	{
	}

	void WindowFrameSystem::End(Scene* pScene)
	{
	}
}
