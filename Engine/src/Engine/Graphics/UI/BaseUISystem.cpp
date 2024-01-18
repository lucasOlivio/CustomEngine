#include "pch.h"

#include "BaseUISystem.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

namespace MyEngine
{
    void BaseUISystem::Init()
    {
        // Initialize all Imgui integration with GLFW and OpenGL
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        WindowComponent* pWindow = GraphicsLocator::GetWindow();

        // Dark theme for the window
        ImGui::StyleColorsDark();

        bool response = ImGui_ImplGlfw_InitForOpenGL(pWindow->pGLFWWindow, true);
        if (!response)
        {
            LOG_ERROR("Error initializing IMGUI with GLFW!");
            return;
        }

        response = ImGui_ImplOpenGL3_Init("#version 420");
        if (!response)
        {
            LOG_ERROR("Error initializing IMGUI with OpenGL!");
            return;
        }

        return;
    }

    void BaseUISystem::Start(Scene* pScene)
    {
    }

    void BaseUISystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void BaseUISystem::Render(Scene* pScene)
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open Project...", "Ctrl+O"))
                    Test();

                ImGui::Separator();

                if (ImGui::MenuItem("New Scene", "Ctrl+N"))
                    Test();

                if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                    Test();

                if (ImGui::MenuItem("Save Scene As...", "Ctrl+Shift+S"))
                    Test();

                ImGui::Separator();

                if (ImGui::MenuItem("Exit"))
                    Test();

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Script"))
            {
                if (ImGui::MenuItem("Reload assembly", "Ctrl+R"))
                    Test();

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void BaseUISystem::End(Scene* pScene)
    {
    }

    void BaseUISystem::Shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
