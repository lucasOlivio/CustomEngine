#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class FrameCollisionLocator
	{
	public:
		static FrameCollisionComponent* Get();

		static void Set(FrameCollisionComponent* pFrameCollision);

	private:
		static FrameCollisionComponent* m_pFrameCollision;
	};
}
