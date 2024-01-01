#include "pch.h"
#include "Engine.h"

namespace MyEngine
{
    Engine::Engine()
    {
        m_pScene = new Scene();
    }

    Engine::~Engine()
    {
        for (iSystem* pSystem : m_systems)
        {
            delete pSystem;
        }
    }

    Scene* Engine::GetScene()
    {
        return m_pScene;
    }

    void Engine::AddSystem(iSystem* pSystem)
    {
        m_systems.push_back(pSystem);
    }

    void Engine::Init()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Start(m_pScene);
        }
    }

    void Engine::Update(float deltaTime)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Update(m_pScene, deltaTime);
        }
    }

    void Engine::Render()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Render(m_pScene);
        }
    }

    void Engine::Shutdown()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->End(m_pScene);
        }
    }
}
