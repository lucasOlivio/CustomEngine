#include "pch.h"

#include "GridBroadphaseLocator.h"

namespace MyEngine
{
    GridBroadphaseComponent* GridBroadphaseLocator::m_pGridBroadphase = new GridBroadphaseComponent();

    GridBroadphaseComponent* GridBroadphaseLocator::Get()
    {
        return m_pGridBroadphase;
    }

    void GridBroadphaseLocator::Set(GridBroadphaseComponent* pGridBroadphase)
    {
        delete m_pGridBroadphase;
        m_pGridBroadphase = pGridBroadphase;
    }
}
