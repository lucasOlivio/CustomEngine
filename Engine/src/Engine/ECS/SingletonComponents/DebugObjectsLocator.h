#pragma once

#include "Engine/ECS/SingletonComponents/Components.h"

namespace MyEngine
{
	class DebugObjectsLocator
	{
	public:
		static DebugSquareComponent* GetSquare();

		static void SetSquare(DebugSquareComponent* pDebugSquare);

	private:
		static DebugSquareComponent* m_pDebugSquare;
	};
}
