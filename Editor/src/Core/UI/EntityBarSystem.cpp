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

        ImGui::Columns(4, nullptr, false);
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("<")) EntitySelector::PrevEntity(pScene);
        ImGui::SameLine();
        if (ImGui::Button(">")) EntitySelector::NextEntity(pScene);
        ImGui::SameLine();
        bool treeEntity = ImGui::TreeNodeEx(sliderTitle.c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);

        TagComponent* pTag = pScene->Get<TagComponent>(entityId);
        if (pTag)
        {
            ImGui::SameLine();
            ImGui::Text((" | TAG: " + pTag->name).c_str());
        }

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
}
