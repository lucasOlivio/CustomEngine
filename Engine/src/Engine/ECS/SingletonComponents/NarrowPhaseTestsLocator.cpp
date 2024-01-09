#include "pch.h"

#include "NarrowPhaseTestsLocator.h"

namespace MyEngine
{
    NarrowPhaseTestsComponent* NarrowPhaseTestsLocator::m_pNarrowPhaseTests = new NarrowPhaseTestsComponent();

    NarrowPhaseTestsComponent* NarrowPhaseTestsLocator::Get()
    {
        return m_pNarrowPhaseTests;
    }

    void NarrowPhaseTestsLocator::Set(NarrowPhaseTestsComponent* pNarrowPhaseTests)
    {
        delete m_pNarrowPhaseTests;
        m_pNarrowPhaseTests = pNarrowPhaseTests;
    }
}
