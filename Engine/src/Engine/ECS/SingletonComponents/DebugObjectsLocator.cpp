#include "pch.h"

#include "DebugObjectsLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"

namespace MyEngine
{
    DebugSquareComponent* DebugObjectsLocator::m_pDebugSquare = new DebugSquareComponent();

    DebugSquareComponent* DebugObjectsLocator::GetSquare()
    {
        return m_pDebugSquare;
    }

    void DebugObjectsLocator::SetSquare(DebugSquareComponent* pDebugSquare)
    {
        delete m_pDebugSquare;
        m_pDebugSquare = pDebugSquare;
    }
}
