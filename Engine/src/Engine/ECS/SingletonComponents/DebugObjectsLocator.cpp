#include "pch.h"

#include "DebugObjectsLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"

namespace MyEngine
{
    DebugSquareComponent* DebugObjectsLocator::m_pDebugSquare = new DebugSquareComponent();
    DebugSphereComponent* DebugObjectsLocator::m_pDebugSphere = new DebugSphereComponent();

    DebugSquareComponent* DebugObjectsLocator::GetSquare()
    {
        return m_pDebugSquare;
    }

    DebugSphereComponent* DebugObjectsLocator::GetSphere()
    {
        return m_pDebugSphere;
    }

    void DebugObjectsLocator::SetSquare(DebugSquareComponent* pDebugSquare)
    {
        delete m_pDebugSquare;
        m_pDebugSquare = pDebugSquare;
    }

    void DebugObjectsLocator::SetSphere(DebugSphereComponent* pDebugSphere)
    {
        delete m_pDebugSphere;
        m_pDebugSphere = pDebugSphere;
    }
}
