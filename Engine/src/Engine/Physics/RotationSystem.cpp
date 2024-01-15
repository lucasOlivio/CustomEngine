#include "pch.h"

#include "RotationSystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    void RotationSystem::Start(Scene* pScene)
    {
    }

    void RotationSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update velocity and position
        for (Entity entityId : SceneView<TransformComponent, RotationComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            RotationComponent* pRotation = pScene->Get<RotationComponent>(entityId);

            pRotation->velocity = pRotation->velocity + (pRotation->acceleration * deltaTime);
            glm::vec3 deltaRotation = pRotation->velocity * deltaTime;

            pTransform->orientation = TransformUtils::AdjustOrientation(pTransform->orientation, deltaRotation);
        }
    }

    void RotationSystem::Render(Scene* pScene)
    {
    }

    void RotationSystem::End(Scene* pScene)
    {
    }
}
