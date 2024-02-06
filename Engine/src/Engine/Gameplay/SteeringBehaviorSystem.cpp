#include "pch.h"

#include "SteeringBehaviorSystem.h"

#include "Engine/Gameplay/GameplayProperties.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"

#include "Engine/Utils/Math.h"
#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void SteeringBehaviorSystem::Init()
    {
    }

    void SteeringBehaviorSystem::Start(Scene* pScene)
    {
    }

    void SteeringBehaviorSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update velocity and position
        for (Entity entityId : SceneView<TransformComponent, MovementComponent, SteeringBehaviorComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            MovementComponent* pMovement = pScene->Get<MovementComponent>(entityId);
            SteeringBehaviorComponent* pSteeringBehavior = pScene->Get<SteeringBehaviorComponent>(entityId);

            TransformComponent* pTransformTarget = pScene->Get<TransformComponent>(pSteeringBehavior->targetId);
            if (!pTransformTarget)
            {
                continue;
            }

            glm::vec3 direction = pTransformTarget->worldPosition - pTransform->worldPosition;
            glm::vec3 directionNormal = glm::normalize(direction);

            // Update facing direction
            glm::vec3 currForward = TransformUtils::GetForwardVector(pTransform->orientation);
            float angle = Angle(currForward, direction, UP_VECTOR); // Get yaw adjust
            pTransform->orientation = TransformUtils::AdjustOrientation(pTransform->orientation,
                                                                        glm::vec3(0.0, angle, 0.0f));

            // Update movement direction
            float distToTarget = glm::distance(pTransformTarget->worldPosition, pTransform->worldPosition);
            if (distToTarget < pSteeringBehavior->maxDistance)
            {
                pMovement->velocity = glm::vec3(0.0f);
                return;
            }
            pMovement->velocity = directionNormal * pSteeringBehavior->speed;
        }
    }

    void SteeringBehaviorSystem::Render(Scene* pScene)
    {
    }

    void SteeringBehaviorSystem::End(Scene* pScene)
    {
    }

    void SteeringBehaviorSystem::Shutdown()
    {
    }
}
