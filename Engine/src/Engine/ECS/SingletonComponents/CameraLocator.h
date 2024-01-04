#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class CameraLocator
	{
	public:
		static CameraComponent* Get();

		static void Set(CameraComponent* pCamera);

	private:
		static CameraComponent* m_pCamera;
	};
}
