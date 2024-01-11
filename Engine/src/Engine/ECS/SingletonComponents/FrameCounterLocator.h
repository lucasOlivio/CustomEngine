#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class FrameCounterLocator
	{
	public:
		static FrameCounterComponent* Get();

		static void Set(FrameCounterComponent* pFrameCounter);

	private:
		static FrameCounterComponent* m_pFrameCounter;
	};
}
