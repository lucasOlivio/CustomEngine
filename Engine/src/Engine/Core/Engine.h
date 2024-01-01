#pragma once

#include "Scene.h"
#include "iSystem.h"

namespace MyEngine
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		// In the absence of managing scene by editor/file use this
		Scene* GetScene();

		// Systems that will update components when simulation is running
		void AddSystem(iSystem* pSystem);

		void Init();

		void Update(float deltaTime);

		void Render();

		void Shutdown();

	private:
		std::vector<iSystem*> m_systems;
		Scene* m_pScene;
	};
}
