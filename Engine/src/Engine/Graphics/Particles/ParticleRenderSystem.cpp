#include "pch.h"

#include "ParticleRenderSystem.h"

#include "Engine/Graphics/Particles/ParticleManagerLocator.h"
#include "Engine/Graphics/Materials/MaterialManagerLocator.h"

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
        iMaterialManager* pMaterialManager = MaterialManagerLocator::Get();

        const std::vector<ParticleProps>& particles = pParticleManager->GetParticles();

        for (int i = 0; i < particles.size(); i++)
        {
            ParticleProps particle = particles[i];

            if (particle.lifetime <= 0.0f || particle.pMesh == nullptr)
            {
                continue;
            }

            // HACK: This could all be avoided by making the particle an entity, with model component etc.
            // Bind material if exists
			MaterialComponent* pMaterial = pMaterialManager->GetMaterialByName(pScene, 
																			   particle.material);
            bool useColorTexture = false;
            bool useDefaultColor = true;
			if (pMaterial)
			{
				pMaterialManager->BindMaterial(pScene, pMaterial->name);
                useColorTexture = true;
                useDefaultColor = false;
			}
            else
            {
                pMaterialManager->UnbindMaterial();
            }

            glm::mat4 matTransform = glm::mat4(1.0);

            TransformUtils::GetTransform(particle.position,
                                         particle.orientation,
                                         particle.scale,
                                         matTransform);

            GraphicsUtils::DrawModel(matTransform,
                                     false,
                                     true,
                                     useDefaultColor,
                                     particle.defaultColor,
                                     useColorTexture,
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
