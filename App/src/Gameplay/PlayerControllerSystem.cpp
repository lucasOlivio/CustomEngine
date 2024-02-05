#include "pch.h"

#include "PlayerControllerSystem.h"


#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"

#include "Engine/Events/InputEvent.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Core/InputProperties.h"

#include "Engine/Utils/InputUtils.h"

namespace MyEngine
{
	void PlayerControllerSystem::Init()
	{
	}

	void PlayerControllerSystem::Start(Scene* pScene)
	{
        // Subscribe to keyboard event
        iEventBus<eInputEvents, KeyboardEvent>* pEventBus = EventBusLocator<eInputEvents, KeyboardEvent>::Get();

        pEventBus->Subscribe(eInputEvents::KEYBOARD, InputTriggered);

        m_InitiateMouseCapture();
	}

	void PlayerControllerSystem::Update(Scene* pScene, float deltaTime)
	{
		KeyInputComponent* pKey = CoreLocator::GetKeyInput();
        for (Entity playerId : SceneView<PlayerComponent, TransformComponent>(*pScene))
        {
            PlayerComponent* pPlayer = pScene->Get<PlayerComponent>(playerId);
            TransformComponent* pTransform = pScene->Get<TransformComponent>(playerId);

            glm::vec3 playerRotation = TransformUtils::GetQuatAsDegrees(pTransform->orientation);

            glm::vec3 playerFront = glm::normalize(TransformUtils::GetForwardVector(pTransform->orientation));
            glm::vec3 playerSides = glm::normalize(glm::cross(playerFront, glm::vec3(UP_VECTOR)));
            glm::vec3 playerUp = glm::normalize(TransformUtils::GetUpVector(pTransform->orientation));

            glm::vec3 moveOffset = glm::vec3(0.0f);

            // Handle key presses for movement
            float speed = -pPlayer->speed; // Camera for now is opposite to player
            if (pKey->key[eKeyCodes::W])
            {
                moveOffset += speed * playerFront * (float)deltaTime;
            }
            if (pKey->key[eKeyCodes::S])
            {
                moveOffset += -(speed * playerFront * (float)deltaTime);
            }
            if (pKey->key[eKeyCodes::A])
            {
                moveOffset += -(speed * playerSides * (float)deltaTime);
            }
            if (pKey->key[eKeyCodes::D])
            {
                moveOffset += speed * playerSides * (float)deltaTime;
            }

            pTransform->position += moveOffset;

            // Mouse position for changing forward direction
            MouseInputComponent* pMouse = CoreLocator::GetMouseInput();

            float xoffset = (pMouse->posX - pMouse->lastPosX) * pMouse->sensitivity;

            // Create quaternions for yaw
            glm::quat yawQuat = glm::angleAxis(-xoffset, glm::vec3(0.0f, 1.0f, 0.0f));

            // Combine pitch and yaw quaternions
            glm::quat orientationChange = yawQuat;

            // Apply the combined quaternion to the player's orientation
            pTransform->orientation = glm::normalize(orientationChange * pTransform->orientation);

            pMouse->lastPosX = pMouse->posX;
            pMouse->lastPosY = pMouse->posY;
        }
	}

	void PlayerControllerSystem::Render(Scene* pScene)
	{
	}

	void PlayerControllerSystem::End(Scene* pScene)
	{
        m_StopMouseCapture();
	}

	void PlayerControllerSystem::Shutdown()
	{
	}

    void PlayerControllerSystem::InputTriggered(const KeyboardEvent& event)
    {
        if (event.keyData.key != eKeyCodes::ESCAPE)
        {
            return;
        }

        // Trigger window close event
        iEventBus<eWindowEvents, WindowCloseEvent>* pEventBus = EventBusLocator<eWindowEvents, WindowCloseEvent>::Get();

        WindowCloseEvent collEvent = WindowCloseEvent();
        pEventBus->Publish(collEvent);
    }

    void PlayerControllerSystem::m_InitiateMouseCapture()
    {
        // Set initial mouse position to consider mouse on center of window
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        if (pMouse->mouseCaptured)
        {
            return;
        }

        WindowComponent* pWindow = GraphicsLocator::GetWindow();

        pMouse->lastPosX = pMouse->posX;
        pMouse->lastPosY = pMouse->posY;

        InputUtils::CaptureMouse(pWindow->pGLFWWindow);
        pMouse->mouseCaptured = true;
        pMouse->sensitivity = DEFAULT_MOUSE_SENSITIVITY;

        return;
    }

    void PlayerControllerSystem::m_StopMouseCapture()
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        if (!pMouse->mouseCaptured)
        {
            return;
        }
        WindowComponent* pWindow = GraphicsLocator::GetWindow();

        InputUtils::ReleaseMouse(pWindow->pGLFWWindow);
        pMouse->mouseCaptured = false;

        return;
    }
}
