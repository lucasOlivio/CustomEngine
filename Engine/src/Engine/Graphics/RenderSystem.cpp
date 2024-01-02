#include "pch.h"

#include "RenderSystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
    void RenderSystem::Start(Scene* pScene)
    {
        // Create sprites objects
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene)) 
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);
        
        }
        return;
    }

    void RenderSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update transform and deltatime for each sprite
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene)) 
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

        }
    }

    void RenderSystem::Render(Scene* pScene)
    {
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene))
        {
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

        }
    }

    void RenderSystem::End(Scene* pScene)
    {
        // Deletes model objects
        for (Entity entityId : SceneView<TransformComponent, SpriteComponent>(*pScene))
        {
            SpriteComponent* pSprite = pScene->Get<SpriteComponent>(entityId);

        }
    }
}
