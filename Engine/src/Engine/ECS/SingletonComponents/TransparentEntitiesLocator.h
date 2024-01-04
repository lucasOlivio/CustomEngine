#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class TransparentEntitiesLocator
	{
	public:
		static TransparentEntitiesComponent* Get();

		static void Set(TransparentEntitiesComponent* pTransparentEntities);

	private:
		static TransparentEntitiesComponent* m_pTransparentEntities;
	};
}
