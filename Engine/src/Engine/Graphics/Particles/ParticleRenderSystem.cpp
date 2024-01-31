#include "pch.h"

#include "ParticleRenderSystem.h"

#include "Engine/Graphics/Particles/ParticleManagerLocator.h"

#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
    void ParticleRenderSystem::Init()
    {
    }

    void ParticleRenderSystem::Start(Scene* pScene)
    {
    }

    void ParticleRenderSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void ParticleRenderSystem::Render(Scene* pScene)
    {
        iParticleManager* pParticleManager = ParticleManagerLocator::Get();

        const std::vector<ParticleProps>& particles = pParticleManager->GetParticles();

        for (int i = 0; i < particles.size(); i++)
        {
            ParticleProps particle = particles[i];

            if (particle.lifetime <= 0.0f || particle.pMesh == nullptr)
            {
                continue;
            }

            // If the model have a parent we must use the parents transform
            glm::mat4 matTransform = glm::mat4(1.0);

            TransformUtils::GetTransform(particle.position,
                                         particle.orientation,
                                         particle.scale,
                                         matTransform);

            GraphicsUtils::DrawModel(matTransform,
                                     false,
                                     false,
                                     true,
                                     glm::vec3(1.0f),
                                     false,
                                     particle.pMesh->VAO_ID,
                                     particle.pMesh->numberOfIndices);
        }
    }

    void ParticleRenderSystem::End(Scene* pScene)
    {
    }

    void ParticleRenderSystem::Shutdown()
    {
    }
}
