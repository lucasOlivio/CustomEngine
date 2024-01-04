#include "pch.h"

#include "WindowLocator.h"

namespace MyEngine
{
    WindowComponent* WindowLocator::m_pWindow = new WindowComponent();

    WindowComponent* WindowLocator::Get()
    {
        return m_pWindow;
    }

    void WindowLocator::Set(WindowComponent* pWindow)
    {
        delete m_pWindow;
        m_pWindow = pWindow;
    }
}
