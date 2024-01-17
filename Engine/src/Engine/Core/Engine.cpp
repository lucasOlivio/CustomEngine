#include "pch.h"

#include "Engine.h"

#include "Engine/Core/Configs/ConfigSerializerFactory.h"

#include "Engine/Events/EventBus.hpp"
#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/Scene/SceneManager.h"
#include "Engine/ECS/Scene/SceneManagerLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"
#include "Engine/ECS/SingletonComponents/DebugLocator.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"
#include "Engine/ECS/SingletonComponents/PhysicsLocator.h"

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
    }

    Engine::~Engine()
    {
    }

    void Engine::AddSystem(iSystem* pSystem)
    {
        m_systems.push_back(pSystem);
    }

    void Engine::Init(std::string initialSceneName)
    {
        // Setting up events
        m_pEventBusWindow = new EventBus<eWindowEvents, WindowCloseEvent>();
        EventBusLocator<eWindowEvents, WindowCloseEvent>::Set(m_pEventBusWindow);

        m_pEventBusCollision = new EventBus<eCollisionEvents, CollisionEnterEvent>();
        EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Set(m_pEventBusCollision);

        m_pEventBusKeyboard = new EventBus<eInputEvents, KeyboardEvent>();
        EventBusLocator<eInputEvents, KeyboardEvent>::Set(m_pEventBusKeyboard);

        m_pEventBusStoppedState = new EventBus<eStateChangeEvents, StoppedStateEvent>();
        EventBusLocator<eStateChangeEvents, StoppedStateEvent>::Set(m_pEventBusStoppedState);

        m_pEventBusRunningState = new EventBus<eStateChangeEvents, RunningStateEvent>();
        EventBusLocator<eStateChangeEvents, RunningStateEvent>::Set(m_pEventBusRunningState);

        m_pEventBusSceneChange = new EventBus<eSceneEvents, SceneChangeEvent>();
        EventBusLocator<eSceneEvents, SceneChangeEvent>::Set(m_pEventBusSceneChange);

        // Setting up resources managers
        m_pSceneManager = new SceneManager();
        SceneManagerLocator::Set(m_pSceneManager);

        m_pVAOManager = new VAOManager();
        VAOManagerLocator::Set(m_pVAOManager);

        m_pShaderManager = new ShaderManager();
        ShaderManagerLocator::Set(m_pShaderManager);

        m_pMaterialManager = new MaterialManager();
        MaterialManagerLocator::Set(m_pMaterialManager);

        m_pTextureManager = new cBasicTextureManager();
        TextureManagerLocator::Set(m_pTextureManager);

        LoadConfigurations();

        // Global events of engine interest
        m_pEventBusSceneChange->Subscribe(eSceneEvents::CHANGE, [this](const SceneChangeEvent& event) { OnSceneChange(event); });

        // Load resources
        ConfigPathComponent* pConfigPaths = CoreLocator::GetConfigPath();
        m_pTextureManager->SetBasePath(pConfigPaths->pathTextures);
        m_pShaderManager->SetBasePath(pConfigPaths->pathShaders);
        m_pVAOManager->SetBasePath(pConfigPaths->pathModels);
        m_pSceneManager->SetBasePath(pConfigPaths->pathScenes);

        InitializeSystems();

        // TODO: Now each resource is been loaded by the systems, 
        // but they should be loaded all here and have separate files
        m_pSceneManager->ChangeScene(initialSceneName);
    }

    void Engine::Run()
    {
        // TODO: Better closing proccess, should come from event
        GLFWwindow* pGLFWWindow = GraphicsLocator::GetWindow()->pGLFWWindow;

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
            pSystem->Update(m_pCurrentScene, deltaTime);
        }
    }

    void Engine::Render()
    {
        // Clear frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Scene* pScene = m_pSceneManager->GetCurrentScene();
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Render(pScene);
        }

        WindowComponent* pWindow = GraphicsLocator::GetWindow();
        glfwSwapBuffers(pWindow->pGLFWWindow);
        glfwPollEvents();
    }

    void Engine::Shutdown()
    {
        EndSystems(m_pCurrentScene);

        ShutdownSystems();

        for (iSystem* pSystem : m_systems)
        {
            delete pSystem;
        }

        // Delete singleton components
        CoreLocator::Clear();
        DebugLocator::Clear();
        GraphicsLocator::Clear();
        PhysicsLocator::Clear();

        // Delete resouce managers
        delete m_pEventBusWindow;
        delete m_pVAOManager;
        delete m_pShaderManager;
        delete m_pMaterialManager;
        delete m_pTextureManager;
        delete m_pSceneManager;
    }

    void Engine::LoadConfigurations()
    {
        iConfigSerializer* pConfigSerializer = ConfigSerializerFactory::CreateConfigSerializer(DEFAULT_CONFIG);
        ConfigPathComponent* pConfigPath = CoreLocator::GetConfigPath();

        pConfigSerializer->DeserializeConfig(DEFAULT_CONFIG);
    }

    void Engine::InitializeSystems()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Init();
        }
    }

    void Engine::StartSystems(Scene* pScene)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Start(pScene);
        }
    }

    void Engine::EndSystems(Scene* pScene)
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->End(pScene);
        }
    }

    void Engine::ShutdownSystems()
    {
        for (iSystem* pSystem : m_systems)
        {
            pSystem->Shutdown();
        }
    }

    void Engine::OnSceneChange(const SceneChangeEvent& event)
    {
        // End old scene
        if (m_pCurrentScene)
        {
            EndSystems(m_pCurrentScene);
        }

        // Start new scene
        m_pCurrentScene = event.pNewScene;
        StartSystems(m_pCurrentScene);
    }

    float Engine::m_GetDeltaTime()
    {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - m_lastTime;
        m_lastTime = currentTime;

        // Clamp delta time to the maximum frame time
        if (deltaTime > FRAME_DURATION) 
        {
            deltaTime = FRAME_DURATION;
        }

        // Add the frame time to the list
        m_frameTimes.push_back(deltaTime);

        // Limit the number of frames
        const size_t maxFrameCount = FRAME_RATE; // Store frame times for a second
        if (m_frameTimes.size() > maxFrameCount) 
        {
            m_frameTimes.erase(m_frameTimes.begin());
        }

        // Calculate the average frame time
        float averageFrameTime = 0;
        for (float time : m_frameTimes) 
        {
            averageFrameTime += time;
        }
        averageFrameTime /= m_frameTimes.size();

        return averageFrameTime;
    }
}
