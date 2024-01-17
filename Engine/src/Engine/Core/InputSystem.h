#pragma once

#include "Engine/ECS/System/iSystem.h"
#include "Engine/Core/InputProperties.h"

namespace MyEngine
{
	// Manages GLFW input related events and keeps input component updated
	class InputSystem : public iSystem
	{
	public:
		InputSystem() = default;
		virtual ~InputSystem() { };

		virtual void Init();

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

		virtual void Shutdown();

		static void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	private:
		static void m_TriggerKey(const sKeyData& collData);
	};
}
