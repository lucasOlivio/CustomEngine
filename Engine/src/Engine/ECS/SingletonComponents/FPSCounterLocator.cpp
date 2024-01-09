#include "pch.h"

#include "FPSCounterLocator.h"

namespace MyEngine
{
    FPSCounterComponent* FPSCounterLocator::m_pFPSCounter = new FPSCounterComponent();

    FPSCounterComponent* FPSCounterLocator::Get()
    {
        return m_pFPSCounter;
    }

    void FPSCounterLocator::Set(FPSCounterComponent* pFPSCounter)
    {
        delete m_pFPSCounter;
        m_pFPSCounter = pFPSCounter;
    }
}
