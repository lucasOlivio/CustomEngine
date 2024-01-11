#include "pch.h"

#include "CoreLocator.h"

namespace MyEngine
{
    ConfigPathComponent* CoreLocator::m_pConfigPath = new ConfigPathComponent();
    FrameCounterComponent* CoreLocator::m_pFrameCounter = new FrameCounterComponent();

    ConfigPathComponent* CoreLocator::GetConfigPath()
    {
        return m_pConfigPath;
    }

    FrameCounterComponent* CoreLocator::GetFrameCounter()
    {
        return m_pFrameCounter;
    }

    void CoreLocator::SetConfigPath(ConfigPathComponent* pConfigPath)
    {
        delete m_pConfigPath;
        m_pConfigPath = pConfigPath;
    }

    void CoreLocator::SetFrameCounter(FrameCounterComponent* pFrameCounter)
    {
        delete m_pFrameCounter;
        m_pFrameCounter = pFrameCounter;
    }
}
