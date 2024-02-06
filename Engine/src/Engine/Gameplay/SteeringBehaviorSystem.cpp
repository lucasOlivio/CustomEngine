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

            switch (pSteeringBehavior->steeringType)
            {
            case eSteeringTypes::PURSUE:
                m_PursueTarget(pTransform->worldPosition, pTransformTarget->worldPosition,
							    pTransform->orientation, pMovement->velocity,
                                pSteeringBehavior->speed, pSteeringBehavior->maxDistance);
                break;
            case eSteeringTypes::FLEE:
                m_FleeFromTarget(pTransform->worldPosition, pTransformTarget->worldPosition,
							    pTransform->orientation, pMovement->velocity,
                                pSteeringBehavior->speed, pSteeringBehavior->maxDistance);
                break;
            default:
                break;
            }
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

    void SteeringBehaviorSystem::m_PursueTarget(const glm::vec3& myPosition, const glm::vec3& targetPosition,
							                    glm::quat& myOrientation, glm::vec3& myVelocity,
							                    float speed, float maxDistance)
    {
        glm::vec3 direction = targetPosition - myPosition;
        glm::vec3 directionNormal = glm::normalize(direction);

        // Update facing direction
        glm::vec3 currForward = TransformUtils::GetForwardVector(myOrientation);
        float angle = Angle(currForward, direction, UP_VECTOR); // Get yaw adjust

        glm::vec3 yaw = angle * UP_VECTOR;
        myOrientation = TransformUtils::AdjustOrientation(myOrientation,
                                                          yaw);

        // Update movement direction
        float distToTarget = glm::distance(targetPosition, myPosition);
        if (distToTarget < maxDistance)
        {
            myVelocity = glm::vec3(0.0f);
            return;
        }
        myVelocity = directionNormal * speed;
    }

    void SteeringBehaviorSystem::m_FleeFromTarget(const glm::vec3& myPosition, const glm::vec3& targetPosition, 
                                                  glm::quat& myOrientation, glm::vec3& myVelocity, 
                                                  float speed, float maxDistance)
    {
        glm::vec3 lockedAxis = glm::vec3(1.0f, 0.0f, 1.0f);
        glm::vec3 direction = -(targetPosition - myPosition);
        glm::vec3 directionNormal = glm::normalize(direction * lockedAxis);

        // Update facing direction
        glm::vec3 currForward = TransformUtils::GetForwardVector(myOrientation);
        float angle = Angle(currForward, direction, UP_VECTOR); // Get yaw adjust

        glm::vec3 yaw = angle * UP_VECTOR;
        myOrientation = TransformUtils::AdjustOrientation(myOrientation,
                                                          yaw);

        // Update movement direction
        float distToTarget = glm::distance(targetPosition, myPosition);
        if (distToTarget > maxDistance)
        {
            myVelocity = glm::vec3(0.0f);
            return;
        }
        myVelocity = directionNormal * speed;
    }
}
