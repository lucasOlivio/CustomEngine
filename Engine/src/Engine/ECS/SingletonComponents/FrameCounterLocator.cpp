#include "pch.h"

#include "FrameCounterLocator.h"

namespace MyEngine
{
    FrameCounterComponent* FrameCounterLocator::m_pFrameCounter = new FrameCounterComponent();

    FrameCounterComponent* FrameCounterLocator::Get()
    {
        return m_pFrameCounter;
    }

    void FrameCounterLocator::Set(FrameCounterComponent* pFrameCounter)
    {
        delete m_pFrameCounter;
        m_pFrameCounter = pFrameCounter;
    }
}
