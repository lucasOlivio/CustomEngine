#include "pch.h"

#include "CoreLocator.h"

namespace MyEngine
{
    ConfigPathComponent* CoreLocator::m_pConfigPath = new ConfigPathComponent();
    FrameCounterComponent* CoreLocator::m_pFrameCounter = new FrameCounterComponent();
    InputComponent* CoreLocator::m_pInput = new InputComponent();
    StateComponent* CoreLocator::m_pState = new StateComponent();

    ConfigPathComponent* CoreLocator::GetConfigPath()
    {
        return m_pConfigPath;
    }

    FrameCounterComponent* CoreLocator::GetFrameCounter()
    {
        return m_pFrameCounter;
    }

    InputComponent* CoreLocator::GetInput()
    {
        return m_pInput;
    }

    StateComponent* CoreLocator::GetState()
    {
        return m_pState;
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

    void CoreLocator::SetInput(InputComponent* pInput)
    {
        delete m_pInput;
        m_pInput = pInput;
    }

    void CoreLocator::SetState(StateComponent* pState)
    {
        delete m_pState;
        m_pState = pState;
    }

    void CoreLocator::Clear()
    {
        delete m_pConfigPath;
        delete m_pFrameCounter;
        delete m_pInput;
        delete m_pState;
    }
}
