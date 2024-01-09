#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class GridBroadphaseLocator
	{
	public:
		static GridBroadphaseComponent* Get();

		static void Set(GridBroadphaseComponent* pGridBroadphase);

	private:
		static GridBroadphaseComponent* m_pGridBroadphase;
	};
}
