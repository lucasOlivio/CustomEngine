#include "pch.h"

#include "SotBodyConstraintsSystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/CoreLocator.h"

#include "Engine/Graphics/VAO/VAOManagerLocator.h"

namespace MyEngine
{
    void SotBodyConstraintsSystem::Init()
    {
    }

    void SotBodyConstraintsSystem::Start(Scene* pScene)
    {
        // Create all particles and springs for the soft body
        for (Entity entityId : SceneView<SoftBodyComponent>(*pScene))
        {
            SoftBodyComponent* pSoftBody = pScene->Get<SoftBodyComponent>(entityId);

            // Create a copy of the mesh into the VAO
            iVAOManager* pVAOManager = VAOManagerLocator::Get();
            std::string meshCopy = pSoftBody->meshName + std::to_string(entityId);
            sMesh* pMesh = pVAOManager->LoadModelCopyIntoVAO(pSoftBody->meshName, true, true, false, meshCopy);

            // Create the particles and constraints based on original location from the mesh
            size_t numParticles = static_cast<size_t>(pMesh->numberOfVertices);
            pSoftBody->vecParticles.resize(numParticles);
            for (unsigned int i = 0; i < pMesh->numberOfVertices;)
            {
                sVertex& pVertexA = pMesh->pVertices[i];
                sVertex& pVertexB = pMesh->pVertices[i + 1];
                sVertex& pVertexC = pMesh->pVertices[i + 2];

                SoftBodyParticle& particleA = pSoftBody->vecParticles[i];
                SoftBodyParticle& particleB = pSoftBody->vecParticles[i + 1];
                SoftBodyParticle& particleC = pSoftBody->vecParticles[i + 2];

                particleA.mass = pSoftBody->defaultParticleMass;
                particleA.position = glm::vec3(pVertexA.x, pVertexA.y, pVertexA.z);

                particleB.mass = pSoftBody->defaultParticleMass;
                particleB.position = glm::vec3(pVertexB.x, pVertexB.y, pVertexB.z);

                particleC.mass = pSoftBody->defaultParticleMass;
                particleC.position = glm::vec3(pVertexC.x, pVertexC.y, pVertexC.z);

                SoftBodySpring springAB;
                springAB.restLength = glm::distance(particleA.position, particleB.position);
                springAB.strength = pSoftBody->defaultSpringStrength;
                springAB.particleA = &particleA;
                springAB.particleB = &particleB;
                pSoftBody->vecSprings.push_back(springAB);

                SoftBodySpring springBC;
                springBC.restLength = glm::distance(particleB.position, particleC.position);
                springBC.strength = pSoftBody->defaultSpringStrength;
                springBC.particleA = &particleB;
                springBC.particleB = &particleC;
                pSoftBody->vecSprings.push_back(springBC);

                SoftBodySpring springCA;
                springCA.restLength = glm::distance(particleC.position, particleA.position);
                springCA.strength = pSoftBody->defaultSpringStrength;
                springCA.particleA = &particleC;
                springCA.particleB = &particleA;
                pSoftBody->vecSprings.push_back(springCA);

                i += 3; // Create triangulated springs to keep the shape
            }
        }
    }

    void SotBodyConstraintsSystem::Update(Scene* pScene, float deltaTime)
    {
        // Update velocity and position
        for (Entity entityId : SceneView<SoftBodyComponent>(*pScene))
        {
            SoftBodyComponent* pSoftBody = pScene->Get<SoftBodyComponent>(entityId);
        }
    }

    void SotBodyConstraintsSystem::Render(Scene* pScene)
    {
    }

    void SotBodyConstraintsSystem::End(Scene* pScene)
    {
    }

    void SotBodyConstraintsSystem::Shutdown()
    {
    }
}
