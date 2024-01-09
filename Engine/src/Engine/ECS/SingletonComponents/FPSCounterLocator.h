#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class FPSCounterLocator
	{
	public:
		static FPSCounterComponent* Get();

		static void Set(FPSCounterComponent* pFPSCounter);

	private:
		static FPSCounterComponent* m_pFPSCounter;
	};
}
