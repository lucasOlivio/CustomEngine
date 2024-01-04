#include "pch.h"

#include "ConfigPathLocator.h"

namespace MyEngine
{
    ConfigPathComponent* ConfigPathLocator::m_pConfigPath = new ConfigPathComponent();

    ConfigPathComponent* ConfigPathLocator::Get()
    {
        return m_pConfigPath;
    }

    void ConfigPathLocator::Set(ConfigPathComponent* pConfigPath)
    {
        delete m_pConfigPath;
        m_pConfigPath = pConfigPath;
    }
}
