#include "pch.h"

#include "MovementSystem.h"
#include "Engine/Core/SceneView.hpp"
#include "Engine/Core/Components.h"

namespace MyEngine
{
    void MovementSystem::Start(Scene* pScene)
    {
    }

    void MovementSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update velocity and position
        for (Entity entityId : SceneView<TransformComponent, MovementComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);

            pMovement->velocity = pMovement->velocity + pMovement->acceleration;
            pTransform->position = pTransform->position + pMovement->velocity;
        }
    }

    void MovementSystem::Render(Scene* pScene)
    {
    }

    void MovementSystem::End(Scene* pScene)
    {
    }
}
