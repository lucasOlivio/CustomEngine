#include "pch.h"

#include "FlyingCameraSystem.h"

#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

#include "Engine/Core/InputProperties.h"

#include "Engine/Utils/InputUtils.h"
#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void FlyingCameraSystem::Init()
    {
    }

    void FlyingCameraSystem::Start(Scene* pScene)
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        pMouse->sensitivity = DEFAULT_MOUSE_SENSITIVITY;
    }

    void FlyingCameraSystem::Update(Scene* pScene, float deltaTime)
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();

        if (pMouse->button[eMouseCodes::MOUSE_BUTTON_1])
        {
            m_InitiateMouseCapture();
            m_UpdateCameraTransform();
        }
        else
        {
            m_StopMouseCapture();
        }
    }

    void FlyingCameraSystem::Render(Scene* pScene)
    {
    }

    void FlyingCameraSystem::End(Scene* pScene)
    {
    }

    void FlyingCameraSystem::Shutdown()
    {
    }

    void FlyingCameraSystem::m_InitiateMouseCapture()
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

        return;
    }

    void FlyingCameraSystem::m_StopMouseCapture()
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

    void FlyingCameraSystem::m_UpdateCameraTransform()
    {
        MouseInputComponent* pMouse = CoreLocator::GetMouseInput();
        CameraComponent* pCamera = GraphicsLocator::GetCamera();

        float xoffset = (pMouse->posX - pMouse->lastPosX) * pMouse->sensitivity;
        float yoffset = (pMouse->posY - pMouse->lastPosY) * pMouse->sensitivity;

        glm::vec3 rotation = TransformUtils::GetQuatAsDegrees(pCamera->orientation);

        rotation.x -= yoffset;
        rotation.y -= xoffset;

        pCamera->orientation = TransformUtils::GetDegreesAsQuat(rotation);

        pMouse->lastPosX = pMouse->posX;
        pMouse->lastPosY = pMouse->posY;
    }
}
