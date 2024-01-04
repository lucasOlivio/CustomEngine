#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class ConfigPathLocator
	{
	public:
		static ConfigPathComponent* Get();

		static void Set(ConfigPathComponent* pConfigPath);

	private:
		static ConfigPathComponent* m_pConfigPath;
	};
}
