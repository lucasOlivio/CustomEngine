#pragma once

#include "Engine/ECS/System/iSystem.h"

namespace MyEngine
{
	// Manages the ImGui per frame and its initialization, should be placed after any interface system to render
	class MenuSystem : public iSystem
	{
	public:
		MenuSystem() = default;
		virtual ~MenuSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

	private:
		void m_Test();

		void m_LoadScene(bool openLoadScene);

		void m_NewScene(bool openNewScene);

		void m_SaveScene();

		void m_PlayScene();

		void m_StopScene();
	};
}
