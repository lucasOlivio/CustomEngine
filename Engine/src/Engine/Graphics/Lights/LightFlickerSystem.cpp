#include "pch.h"

#include "LightFlickerSystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/Utils/Random.h"

void MyEngine::LightFlickerSystem::Start(Scene* pScene)
{
}

void MyEngine::LightFlickerSystem::Update(Scene* pScene, float deltaTime)
{
    // Update flickering offset
    for (Entity entityId : SceneView<LightComponent>(*pScene))
    {
        LightComponent* pLight = pScene->Get<LightComponent>(entityId);

        if (pLight->params.w == 1)
        {
            // Modulate the light attenuation by changing the offset proportion randomly over time
            float max = 1.08f;
            float min = 0.92f;

            uint32_t seed = (uint32_t)entityId;
            pLight->flickerOffset = glm::vec4(Random::Vec3(seed, min, max), 0);
        }
    }
}

void MyEngine::LightFlickerSystem::Render(Scene* pScene)
{
}

void MyEngine::LightFlickerSystem::End(Scene* pScene)
{
}
