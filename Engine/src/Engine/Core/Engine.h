#pragma once

#include "Engine/ECS/Scene.h"
#include "Engine/ECS/iSystem.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Events/CollisionEvent.h"
#include "Engine/Events/iEventBus.h"
#include "Engine/Graphics/VAO/iVAOManager.h"
#include "Engine/Graphics/Shaders/iShaderManager.h"
#include "Engine/Graphics/Materials/iMaterialManager.h"
#include "Engine/Graphics/Textures/iTextureManager.h"

namespace MyEngine
{
	// App should inherit from this class to setup and run everything needed
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		// Systems that will update components when simulation is running
		virtual void AddSystem(iSystem* pSystem);

		virtual void Init();

		virtual void Run();

		virtual void Update(float deltaTime);

		virtual void Render();

		virtual void Shutdown();

	protected:
		std::vector<iSystem*> m_systems;
		Scene* m_pScene;

		iEventBus<eWindowEvents, WindowCloseEvent>* m_pEventBusWindow;
		iEventBus<eCollisionEvents, CollisionEnterEvent>* m_pEventBusCollision;
		iVAOManager* m_pVAOManager;
		iShaderManager* m_pShaderManager;
		iMaterialManager* m_pMaterialManager;
		iTextureManager* m_pTextureManager;

		float m_lastTime = 0.0f;
		std::vector<float> m_frameTimes;

		float m_GetDeltaTime();
	};
}
