#include "pch.h"

#include "WindowFPSSystem.h"
#include "Engine/ECS/SingletonComponents/WindowLocator.h"
#include "Engine/ECS/SingletonComponents/FPSCounterLocator.h"

namespace MyEngine
{
	void WindowFPSSystem::Start(Scene* pScene)
	{
	}

	void WindowFPSSystem::Update(Scene* pScene, float deltaTime)
	{
		FPSCounterComponent* pFPS = FPSCounterLocator::Get();

		pFPS->frameCount++;

		pFPS->fpsTimer += deltaTime;

		// Update FPS every second in the title
		if (pFPS->fpsTimer >= 1.0f)
		{
			pFPS->currentFPS = (float)(pFPS->frameCount) / pFPS->fpsTimer;

			// Update window name
			WindowComponent* pWindow = WindowLocator::Get();
			pWindow->name = std::to_string(pFPS->currentFPS);

			pFPS->frameCount = 0;
			pFPS->fpsTimer = 0.0f;
		}
	}

	void WindowFPSSystem::Render(Scene* pScene)
	{
	}

	void WindowFPSSystem::End(Scene* pScene)
	{
	}
}
