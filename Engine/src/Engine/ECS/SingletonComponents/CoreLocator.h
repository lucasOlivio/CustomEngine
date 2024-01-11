#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class CoreLocator
	{
	public:
		static ConfigPathComponent* GetConfigPath();
		static FrameCounterComponent* GetFrameCounter();

		static void SetConfigPath(ConfigPathComponent* pConfigPath);
		static void SetFrameCounter(FrameCounterComponent* pFrameCounter);

	private:
		static ConfigPathComponent* m_pConfigPath;
		static FrameCounterComponent* m_pFrameCounter;
	};
}
