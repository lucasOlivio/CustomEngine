#include "pch.h"

#include "WindowFPSSystem.h"
#include "Engine/ECS/SingletonComponents/WindowLocator.h"

namespace MyEngine
{
	void WindowFPSSystem::Start(Scene* pScene)
	{
	}

	void WindowFPSSystem::Update(Scene* pScene, float deltaTime)
	{
		m_frameCount++;

		m_fpsTimer += deltaTime;

		// Update FPS every second in the title
		if (m_fpsTimer >= 1.0f)
		{
			m_currentFPS = (float)(m_frameCount) / m_fpsTimer;

			// Update window name
			WindowComponent* pWindow = WindowLocator::Get();
			pWindow->name = std::to_string(m_currentFPS);

			m_frameCount = 0;
			m_fpsTimer = 0.0f;
		}
	}

	void WindowFPSSystem::Render(Scene* pScene)
	{
	}

	void WindowFPSSystem::End(Scene* pScene)
	{
	}
}
