#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class NarrowPhaseTestsLocator
	{
	public:
		static NarrowPhaseTestsComponent* Get();

		static void Set(NarrowPhaseTestsComponent* pNarrowPhaseTests);

	private:
		static NarrowPhaseTestsComponent* m_pNarrowPhaseTests;
	};
}
