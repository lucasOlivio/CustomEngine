#include "pch.h"

#include "Engine.h"
#include "Engine/Events/EventBus.hpp"
#include "Engine/Events/EventBusLocator.hpp"
#include "Engine/ECS/SingletonComponents/WindowLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"
#include "Engine/Graphics/VAO/VAOManager.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"
#include "Engine/Graphics/Shaders/ShaderManagerLocator.h"
#include "Engine/Graphics/Materials/MaterialManager.h"
#include "Engine/Graphics/Materials/MaterialManagerLocator.h"
#include "Engine/Graphics/Textures/cBasicTextureManager.h"
#include "Engine/Graphics/Textures/TextureManagerLocator.h"

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

    void Engine::AddSystem(iSystem* pSystem)
    {
        m_systems.push_back(pSystem);
    }

    void Engine::Init()
    {
        // Setting up events
        m_pEventBusWindow = new EventBus<eWindowEvents>();
        EventBusLocator<eWindowEvents>::Set(m_pEventBusWindow);

        // Setting up VAO manager
        m_pVAOManager = new VAOManager();
        VAOManagerLocator::Set(m_pVAOManager);

        // Setting up Shader manager
        m_pShaderManager = new ShaderManager();
        ShaderManagerLocator::Set(m_pShaderManager);

        // Setting up Material manager
        m_pMaterialManager = new MaterialManager();
        MaterialManagerLocator::Set(m_pMaterialManager);

        // Setting up Texture manager
        m_pTextureManager = new cBasicTextureManager();
        TextureManagerLocator::Set(m_pTextureManager);

        // Setting up systems
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Start(m_pScene);
        }
    }

    void Engine::Run()
    {
        // TODO: Better closing proccess, should come from event
        GLFWwindow* pGLFWWindow = WindowLocator::Get()->pGLFWWindow;
        while (!glfwWindowShouldClose(pGLFWWindow))
        {
            float deltaTime = m_GetDeltaTime();
            Update(deltaTime);

            Render();
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
        // Clear frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (iSystem* pSystem : m_systems)
        {
            pSystem->Render(m_pScene);
        }

        WindowComponent* pWindow = WindowLocator::Get();
        glfwSwapBuffers(pWindow->pGLFWWindow);
        glfwPollEvents();
    }

    void Engine::Shutdown()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->End(m_pScene);
        }

        for (iSystem* pSystem : m_systems)
        {
            delete pSystem;
        }

        delete m_pScene;
        delete m_pEventBusWindow;
        delete m_pVAOManager;
        delete m_pShaderManager;
        delete m_pMaterialManager;
        delete m_pTextureManager;
    }

    float Engine::m_GetDeltaTime()
    {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        // Clamp delta time to the maximum frame time
        if (deltaTime > FRAME_DURATION) {
            deltaTime = FRAME_DURATION;
        }

        // Add the frame time to the list
        m_frameTimes.push_back(deltaTime);

        // Limit the number of frames
        const size_t maxFrameCount = 60; // Store frame times for a second
        if (m_frameTimes.size() > maxFrameCount) {
            m_frameTimes.erase(m_frameTimes.begin());
        }

        // Calculate the average frame time
        float averageFrameTime = 0;
        for (float time : m_frameTimes) {
            averageFrameTime += time;
        }
        averageFrameTime /= m_frameTimes.size();

        return averageFrameTime;
    }
}
