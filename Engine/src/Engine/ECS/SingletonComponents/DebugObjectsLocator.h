#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class DebugObjectsLocator
	{
	public:
		static DebugSquareComponent* GetSquare();
		static DebugSphereComponent* GetSphere();

		static void SetSquare(DebugSquareComponent* pDebugSquare);
		static void SetSphere(DebugSphereComponent* pDebugSphere);

	private:
		static DebugSquareComponent* m_pDebugSquare;
		static DebugSphereComponent* m_pDebugSphere;
	};
}
