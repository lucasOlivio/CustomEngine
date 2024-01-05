#include "pch.h"

#include "GravitySystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
    void GravitySystem::Start(Scene* pScene)
    {
    }

    void GravitySystem::Update(Scene* pScene, float deltaTime)
    {
        // Update velocity and position
        for (Entity entityId : SceneView<MovementComponent, GravityComponent>(*pScene))
        {
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);
            GravityComponent* pGravity = pScene->Get<GravityComponent>(entityId);

            pMovement->velocity = pMovement->velocity + (pGravity->acceleration * deltaTime);
        }
    }

    void GravitySystem::Render(Scene* pScene)
    {
    }

    void GravitySystem::End(Scene* pScene)
    {
    }
}
