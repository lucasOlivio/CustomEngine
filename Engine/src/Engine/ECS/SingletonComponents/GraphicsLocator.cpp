#include "pch.h"

#include "GraphicsLocator.h"

namespace MyEngine
{
    CameraComponent* GraphicsLocator::m_pCamera = new CameraComponent();
    TransparentEntitiesComponent* GraphicsLocator::m_pTransparentEntities = new TransparentEntitiesComponent();
    WindowComponent* GraphicsLocator::m_pWindow = new WindowComponent();
    AnimationControllerComponent* GraphicsLocator::m_pAnimationController = new AnimationControllerComponent();

    CameraComponent* GraphicsLocator::GetCamera()
    {
        return m_pCamera;
    }

    TransparentEntitiesComponent* GraphicsLocator::GetTransparentEntities()
    {
        return m_pTransparentEntities;
    }

    WindowComponent* GraphicsLocator::GetWindow()
    {
        return m_pWindow;
    }

    AnimationControllerComponent* GraphicsLocator::GetAnimationController()
    {
        return m_pAnimationController;
    }

    void GraphicsLocator::SetCamera(CameraComponent* pCamera)
    {
        delete m_pCamera;
        m_pCamera = pCamera;
    }

    void GraphicsLocator::SetTransparentEntities(TransparentEntitiesComponent* pTransparentEntities)
    {
        delete m_pTransparentEntities;
        m_pTransparentEntities = pTransparentEntities;
    }

    void GraphicsLocator::SetWindow(WindowComponent* pWindow)
    {
        delete m_pWindow;
        m_pWindow = pWindow;
    }

    void GraphicsLocator::SetAnimationController(AnimationControllerComponent* pAnimationController)
    {
        delete m_pAnimationController;
        m_pAnimationController = pAnimationController;
    }

    void GraphicsLocator::Clear()
    {
        delete m_pCamera;
        delete m_pTransparentEntities;
        delete m_pWindow;
        delete m_pAnimationController;
    }
}
