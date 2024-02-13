#include "pch.h"

#include "SotBodyConstraintsSystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/DebugLocator.h"

#include "Engine/Graphics/VAO/VAOManagerLocator.h"
#include "Engine/Graphics/Renderer/RendererManagerLocator.h"

#include "Engine/Utils/TransformUtils.h"

namespace MyEngine
{
    const std::string PREFIX_MESH = "softbody-";

    void SotBodyConstraintsSystem::Init()
    {
    }

    void SotBodyConstraintsSystem::Start(Scene* pScene)
    {
        iVAOManager* pVAOManager = VAOManagerLocator::Get();

        // Create all particles and springs for the soft body
        for (Entity entityId : SceneView<TransformComponent, SoftBodyComponent>(*pScene))
        {
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
            SoftBodyComponent* pSoftBody = pScene->Get<SoftBodyComponent>(entityId);

            // Create a copy of the mesh into the VAO
            std::string meshCopy = PREFIX_MESH + pSoftBody->meshName + std::to_string(entityId);
            sMesh* pMesh = pVAOManager->LoadModelCopyIntoVAO(pSoftBody->meshName, true, true, false, meshCopy);

            // Create the particles and constraints based on original location from the mesh
            size_t numParticles = static_cast<size_t>(pMesh->numberOfVertices);

            pSoftBody->vecSprings.clear();
            pSoftBody->vecParticles.clear();
            pSoftBody->vecParticles.reserve(numParticles);
            
            for (unsigned int i = 0; i < pMesh->numberOfTriangles; i++)
            {
                glm::vec3 vertexA = pMesh->pTriangles[i].vertices[0];
                glm::vec3 vertexB = pMesh->pTriangles[i].vertices[1];
                glm::vec3 vertexC = pMesh->pTriangles[i].vertices[2];

                SoftBodyParticle* particleA = new SoftBodyParticle();
                SoftBodyParticle* particleB = new SoftBodyParticle();
                SoftBodyParticle* particleC = new SoftBodyParticle();

                pSoftBody->vecParticles.push_back(particleA);
                pSoftBody->vecParticles.push_back(particleB);
                pSoftBody->vecParticles.push_back(particleC);

                glm::mat4 transfMat = glm::mat4(1.0f);
                particleA->mass = pSoftBody->defaultParticleMass;
                particleA->position = vertexA;
                particleA->position = TransformUtils::LocalToWorldPoint(particleA->position,
                                                                      pTransform->worldPosition,
                                                                      pTransform->worldOrientation,
                                                                      pTransform->worldScale, transfMat);

                transfMat = glm::mat4(1.0f);
                particleB->mass = pSoftBody->defaultParticleMass;
                particleB->position = vertexB;
                particleB->position = TransformUtils::LocalToWorldPoint(particleB->position,
                                                                      pTransform->worldPosition,
                                                                      pTransform->worldOrientation,
                                                                      pTransform->worldScale, transfMat);

                transfMat = glm::mat4(1.0f);
                particleC->mass = pSoftBody->defaultParticleMass;
                particleC->position = vertexC;
                particleC->position = TransformUtils::LocalToWorldPoint(particleC->position,
                                                                      pTransform->worldPosition,
                                                                      pTransform->worldOrientation,
                                                                      pTransform->worldScale, transfMat);

                SoftBodySpring* pSpringAB = new SoftBodySpring();
                pSpringAB->restLength = glm::distance(particleA->position, particleB->position);
                pSpringAB->strength = pSoftBody->defaultSpringStrength;
                pSpringAB->particleA = particleA;
                pSpringAB->particleB = particleB;
                pSoftBody->vecSprings.push_back(pSpringAB);

                SoftBodySpring* pSpringBC = new SoftBodySpring();
                pSpringBC->restLength = glm::distance(particleB->position, particleC->position);
                pSpringBC->strength = pSoftBody->defaultSpringStrength;
                pSpringBC->particleA = particleB;
                pSpringBC->particleB = particleC;
                pSoftBody->vecSprings.push_back(pSpringBC);

                SoftBodySpring* springCA = new SoftBodySpring();
                springCA->restLength = glm::distance(particleC->position, particleA->position);
                springCA->strength = pSoftBody->defaultSpringStrength;
                springCA->particleA = particleC;
                springCA->particleB = particleA;
                pSoftBody->vecSprings.push_back(springCA);

                i += 3; // Create triangulated springs to keep the shape
            }

            std::cout << std::endl;
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
        iRendererManager* pRendererManager = RendererManagerLocator::Get();
        iVAOManager* pVAOManager = VAOManagerLocator::Get();
        DebugSphereComponent* pSphere = DebugLocator::GetSphere();

        for (Entity entityId : SceneView<SoftBodyComponent>(*pScene))
        {
            SoftBodyComponent* pSoftBody = pScene->Get<SoftBodyComponent>(entityId);

            for (SoftBodyParticle* particle : pSoftBody->vecParticles)
            {
                glm::mat4 matTransf = glm::mat4(1.0f);
                TransformUtils::GetTransform(particle->position, 0.5f, matTransf);

                sRenderModelInfo renderInfo = sRenderModelInfo();
                renderInfo.matModel = matTransf;
                renderInfo.VAO_ID = pSphere->pMesh->VAO_ID;
                renderInfo.numberOfIndices = pSphere->pMesh->numberOfIndices;
                renderInfo.isWireFrame = true;
                renderInfo.doNotLight = true;
                renderInfo.useDebugColor = true;
                renderInfo.debugColor = BLUE;

                for (uint fboid : pSphere->FBOIDs)
                {
                    pRendererManager->AddToRender(fboid, renderInfo);
                }
            }
        }
    }

    void SotBodyConstraintsSystem::End(Scene* pScene)
    {
    }

    void SotBodyConstraintsSystem::Shutdown()
    {
    }
}
