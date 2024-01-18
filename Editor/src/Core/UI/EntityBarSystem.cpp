#include "pch.h"

#include "EntityBarSystem.h"

#include "Utils/EntitySelector.h"
#include "Utils/ComponentUI.h"

#include "Engine/ECS/Components.h"
#include "Engine/ECS/Scene/SceneManagerLocator.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Events/EventBusLocator.hpp"

#include "Engine/Utils/Files.h"

namespace MyEngine
{
    void EntityBarSystem::Init()
    {
    }

    void EntityBarSystem::Start(Scene* pScene)
    {
        ComponentUI::MapComponentsUI(pScene);
    }

    void EntityBarSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void EntityBarSystem::Render(Scene* pScene)
    {
        Entity entityId = EntitySelector::GetSelectedEntity();
        std::string sliderTitle = "Entity #" + std::to_string(entityId);

        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("DUPLICATE ENTITY"))
        {
            m_CreateEntity(pScene, entityId);
        }
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        if (ImGui::Button("NEW ENTITY"))
        {
            m_CreateEntity(pScene);
        }
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        if (ImGui::Button("<"))
        {
            EntitySelector::PrevEntity(pScene);
        }
        ImGui::SameLine();
        if (ImGui::Button(">"))
        {
            EntitySelector::NextEntity(pScene);
        }
        ImGui::SameLine();
        bool treeEntity = ImGui::TreeNodeEx(sliderTitle.c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);

        TagComponent* pTag = pScene->Get<TagComponent>(entityId);
        if (pTag)
        {
            ImGui::SameLine();
            ImGui::Text((" | TAG: " + pTag->name).c_str());
        }

        ImGui::Columns(4, nullptr, false);
        if (treeEntity)
        {
            ComponentUI::GenerateComponentsUI(pScene, entityId);
            ImGui::TreePop();
        }
    }

    void EntityBarSystem::End(Scene* pScene)
    {
    }

    void EntityBarSystem::Shutdown()
    {
    }

    void EntityBarSystem::m_CreateEntity(Scene* pScene)
    {
        Entity entityId = pScene->CreateEntity(true);
        EntitySelector::SetSelectedEntity(entityId);
    }

    void EntityBarSystem::m_CreateEntity(Scene* pScene, Entity entityId)
    {
        Entity newEntityId = pScene->CreateEntity(entityId);
        EntitySelector::SetSelectedEntity(newEntityId);
    }
}
