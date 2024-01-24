#include "pch.h"

#include "AnimationPlayerSystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"

#include "Engine/Utils/AnimationUtils.h"

namespace MyEngine
{
    void AnimationPlayerSystem::Init()
    {
    }

    void AnimationPlayerSystem::Start(Scene* pScene)
    {
    }

    void AnimationPlayerSystem::Update(Scene* pScene, float deltaTime)
    {
        for (Entity entityId : SceneView<TransformComponent, TransformAnimationComponent>(*pScene))
        {
            TransformAnimationComponent* pAnimation = pScene->Get<TransformAnimationComponent>(entityId);

            pAnimation->time += deltaTime;
        }
    }

    void AnimationPlayerSystem::Render(Scene* pScene)
    {
    }

    void AnimationPlayerSystem::End(Scene* pScene)
    {
    }

    void AnimationPlayerSystem::Shutdown()
    {
    }
}
