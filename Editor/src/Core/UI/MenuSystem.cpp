#include "pch.h"

#include "MenuSystem.h"
#include "Engine/ECS/SingletonComponents/GraphicsLocator.h"

namespace MyEngine
{
    void MenuSystem::Init()
    {
    }

    void MenuSystem::Start(Scene* pScene)
    {
    }

    void MenuSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void MenuSystem::Render(Scene* pScene)
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

    void MenuSystem::End(Scene* pScene)
    {
    }

    void MenuSystem::Shutdown()
    {
    }

    void MenuSystem::Test()
    {
    }
}
