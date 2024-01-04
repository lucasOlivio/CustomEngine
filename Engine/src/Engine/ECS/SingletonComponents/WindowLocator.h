#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class WindowLocator
	{
	public:
		static WindowComponent* Get();

		static void Set(WindowComponent* pWindow);

	private:
		static WindowComponent* m_pWindow;
	};
}
