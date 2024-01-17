#include "pch.h"

#include "InputSystem.h"

#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/InputEvent.h"
#include "Engine/Events/EventBusLocator.hpp"

namespace MyEngine
{
	void InputSystem::Init()
	{
		// TODO: Remove this coupling, this creates the need to the input system 
		// be registered after the window system
		WindowComponent* pWindow = GraphicsLocator::GetWindow();
		if (pWindow->pGLFWWindow)
		{
			glfwSetKeyCallback(pWindow->pGLFWWindow, InputSystem::InputCallback);
		}
	}

	void InputSystem::Start(Scene* pScene)
	{
	}

	void InputSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void InputSystem::Render(Scene* pScene)
	{
	}

	void InputSystem::End(Scene* pScene)
	{
	}

	void InputSystem::Shutdown()
	{
	}

	void InputSystem::InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		// Update input component to keep track of pressed keys
		InputComponent* pInput = CoreLocator::GetInput();

		sKeyData keyData = sKeyData();
		keyData.key = (eKeyCodes)key;
		keyData.action = (eKeyActions)action;
		keyData.mod = (eKeyMods)mods;
		
		if (keyData.action == eKeyActions::KEY_RELEASE)
		{
			pInput->key[key] = false;
		}
		else
		{
			pInput->key[key] = true;
		}

		// Push keyboard event
		m_TriggerKey(keyData);
	}

	void InputSystem::m_TriggerKey(const sKeyData& collData)
	{
		iEventBus<eInputEvents, KeyboardEvent>* pEventBus = EventBusLocator<eInputEvents, KeyboardEvent>::Get();

		KeyboardEvent keyEvent = KeyboardEvent();
		keyEvent.keyData = collData;
		pEventBus->Publish(keyEvent);
	}
}
