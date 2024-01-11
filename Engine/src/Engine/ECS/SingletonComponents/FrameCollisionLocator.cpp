#include "pch.h"

#include "FrameCollisionLocator.h"

namespace MyEngine
{
    FrameCollisionComponent* FrameCollisionLocator::m_pFrameCollision = new FrameCollisionComponent();

    FrameCollisionComponent* FrameCollisionLocator::Get()
    {
        return m_pFrameCollision;
    }

    void FrameCollisionLocator::Set(FrameCollisionComponent* pFrameCollision)
    {
        delete m_pFrameCollision;
        m_pFrameCollision = pFrameCollision;
    }
}
