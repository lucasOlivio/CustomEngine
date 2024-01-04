#include "pch.h"

#include "CameraLocator.h"

namespace MyEngine
{
    CameraComponent* CameraLocator::m_pCamera = new CameraComponent();

    CameraComponent* CameraLocator::Get()
    {
        return m_pCamera;
    }

    void CameraLocator::Set(CameraComponent* pCamera)
    {
        delete m_pCamera;
        m_pCamera = pCamera;
    }
}
