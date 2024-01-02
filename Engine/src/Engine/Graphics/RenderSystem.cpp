#include "pch.h"

#include "RenderSystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
    void RenderSystem::Start(Scene* pScene)
    {
        // Create model objects
        for (Entity entityId : SceneView<TransformComponent, ModelComponent>(*pScene)) 
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
        
        }
        return;
    }

    void RenderSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update transform and deltatime for each model
        for (Entity entityId : SceneView<TransformComponent, ModelComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);

        }
    }

    void RenderSystem::Render(Scene* pScene)
    {
        for (Entity entityId : SceneView<TransformComponent, ModelComponent>(*pScene))
        {
            ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);

        }
    }

    void RenderSystem::End(Scene* pScene)
    {
        // Deletes model objects
        for (Entity entityId : SceneView<TransformComponent, ModelComponent>(*pScene))
        {
            ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);

        }
    }
}
