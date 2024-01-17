#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class CoreLocator
	{
	public:
		static ConfigPathComponent* GetConfigPath();
		static FrameCounterComponent* GetFrameCounter();
		static InputComponent* GetInput();
		static StateComponent* GetState();

		static void SetConfigPath(ConfigPathComponent* pConfigPath);
		static void SetFrameCounter(FrameCounterComponent* pFrameCounter);
		static void SetInput(InputComponent* pInput);
		static void SetState(StateComponent* pState);

		static void Clear();

	private:
		static ConfigPathComponent* m_pConfigPath;
		static FrameCounterComponent* m_pFrameCounter;
		static InputComponent* m_pInput;
		static StateComponent* m_pState;
	};
}
