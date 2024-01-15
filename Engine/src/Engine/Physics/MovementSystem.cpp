#include "pch.h"

#include "MovementSystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/Utils/TransformUtils.h"

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

            pMovement->velocity = pMovement->velocity + (pMovement->acceleration * deltaTime);
            pTransform->position = pTransform->position + (pMovement->velocity * deltaTime);
        }
    }

    void MovementSystem::Render(Scene* pScene)
    {
    }

    void MovementSystem::End(Scene* pScene)
    {
    }
}
