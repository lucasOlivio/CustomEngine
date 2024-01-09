#include "pch.h"

#include "CheckOverlapSystem.h"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SingletonComponents/NarrowPhaseTestsLocator.h"
#include "Engine/Utils/CollisionsUtils.h"

namespace MyEngine
{
    void CheckOverlapSystem::Start(Scene* pScene)
    {
    }

    void CheckOverlapSystem::Update(Scene* pScene, float deltaTime)
    {
        NarrowPhaseTestsComponent* pTests = NarrowPhaseTestsLocator::Get();

        // The first layer is the grouping of objects to test
        for (int group = 0; group < pTests->nonStaticEntitiesToTest.size(); group++)
        {
            std::vector<Entity> nonStaticGroup = pTests->nonStaticEntitiesToTest[group];
            std::vector<Entity> staticGroup = pTests->staticEntitiesToTest[group];
            std::vector<sTriangle*> trianglesGroup = pTests->trianglesToTest[group];

            for (int i = 0; i < nonStaticGroup.size(); i++)
            {
                Entity entityId = nonStaticGroup[i];
                TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
                RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

                // Get the right collider to test against
                SphereColliderComponent* pSphere;
                AABBColliderComponent* pAABB;
                switch (pRigidBody->shapeType)
                {
                case eShape::SPHERE:
                    pSphere = pScene->Get<SphereColliderComponent>(entityId);
                    m_CheckSphereOverlaps(pScene, pTransform, pSphere, i,
                                          nonStaticGroup,
                                          staticGroup,
                                          trianglesGroup);
                    break;
                case eShape::AABB:
                    pAABB = pScene->Get<AABBColliderComponent>(entityId);
                    m_CheckAABBOverlaps(pScene, pTransform, pAABB, i,
                                        nonStaticGroup,
                                        staticGroup,
                                        trianglesGroup);
                    break;
                default:
                    LOG_WARNING("Unknown shape for entity " + std::to_string(entityId));
                    continue;
                }

            }
        }
    }

    void CheckOverlapSystem::Render(Scene* pScene)
    {
    }

    void CheckOverlapSystem::End(Scene* pScene)
    {
    }

    void CheckOverlapSystem::m_CheckSphereOverlaps(Scene* pScene,
								                   TransformComponent* pTransformA,
								                   SphereColliderComponent* pSphereA,
								                   const int index,
                                                   const std::vector<Entity>& nonStaticEntities,
                                                   const std::vector<Entity>& staticEntities,
                                                   const std::vector<sTriangle*>& triangles)
    {
        // Start from one entity ahead so we dont test repeated
        for (int j = index + 1; j < nonStaticEntities.size(); j++)
        {
            Entity entityIdB = nonStaticEntities[j];
            bool isCollision = m_CheckSphereEntityOverlap(pScene, entityIdB,
                                       pTransformA, 
                                       pSphereA);
        }

        for (int j = 0; j < staticEntities.size(); j++)
        {
            Entity entityIdB = nonStaticEntities[j];
            bool isCollision = m_CheckSphereEntityOverlap(pScene, entityIdB,
                                       pTransformA, 
                                       pSphereA);
        }

        for (int j = 0; j < triangles.size(); j++)
        {
            bool isCollision = CollisionsUtils::SphereTriangle_Overlap(pSphereA->radius,
                                                                       pTransformA->position,
                                                                       pTransformA->scale,
                                                                       triangles[j]->vertices[0],
                                                                       triangles[j]->vertices[1],
                                                                       triangles[j]->vertices[2]);
        }
    }

    bool CheckOverlapSystem::m_CheckSphereEntityOverlap(Scene* pScene, Entity entityIdB,
                                                        TransformComponent* pTransformA, 
                                                        SphereColliderComponent* pSphereA)
    {
        TransformComponent* pTransformB = pScene->Get<TransformComponent>(entityIdB);
        RigidBodyComponent* pRigidBodyB = pScene->Get<RigidBodyComponent>(entityIdB);

        // Get the right collider to test against
        bool isCollision = false;
        switch (pRigidBodyB->shapeType)
        {
        case eShape::SPHERE:
        {
            SphereColliderComponent* pSphereB = pScene->Get<SphereColliderComponent>(entityIdB);
            isCollision = CollisionsUtils::SphereSphere_Overlap(pSphereA->radius,
                                                                pTransformA->position,
                                                                pTransformA->scale,
                                                                pSphereB->radius,
                                                                pTransformB->position,
                                                                pTransformB->scale);
            break;
        }
        case eShape::AABB:
        {
            AABBColliderComponent* pAABBB = pScene->Get<AABBColliderComponent>(entityIdB);
            isCollision = CollisionsUtils::SphereAABB_Overlap(pSphereA->radius,
                                                              pTransformA->position,
                                                              pTransformA->scale,
                                                              pAABBB->min,
                                                              pAABBB->max,
                                                              pTransformB->position,
                                                              pTransformB->scale);
            break;
        }
        default:
            LOG_WARNING("Unknown shape for entity " + std::to_string(entityIdB));
            return false;
        }

        return isCollision;
    }

    void CheckOverlapSystem::m_CheckAABBOverlaps(Scene* pScene,
								                 TransformComponent* pTransformA,
								                 AABBColliderComponent* pAABBA,
								                 const int index,
                                                 const std::vector<Entity>& nonStaticEntities,
                                                 const std::vector<Entity>& staticEntities,
                                                 const std::vector<sTriangle*>& triangles)
    {
        // Start from one entity ahead so we dont test repeated
        for (int j = index + 1; j < nonStaticEntities.size(); j++)
        {
            Entity entityIdB = nonStaticEntities[j];
            bool isCollision = m_CheckAABBEntityOverlap(pScene, entityIdB,
                                                        pTransformA, 
                                                        pAABBA);
        }

        for (int j = 0; j < staticEntities.size(); j++)
        {
            Entity entityIdB = nonStaticEntities[j];
            bool isCollision = m_CheckAABBEntityOverlap(pScene, entityIdB,
                                                        pTransformA, 
                                                        pAABBA);
        }

        for (int j = 0; j < triangles.size(); j++)
        {
            bool isCollision = CollisionsUtils::AABBTriangle_Overlap(pAABBA->min, pAABBA->max,
                                                                     pTransformA->position,
                                                                     pTransformA->scale,
                                                                     triangles[j]->vertices[0],
                                                                     triangles[j]->vertices[1],
                                                                     triangles[j]->vertices[2]);
        }
    }

    bool CheckOverlapSystem::m_CheckAABBEntityOverlap(Scene* pScene, Entity entityIdB,
                                                      TransformComponent* pTransformA,
                                                      AABBColliderComponent* pAABBA)
    {
        TransformComponent* pTransformB = pScene->Get<TransformComponent>(entityIdB);
        RigidBodyComponent* pRigidBodyB = pScene->Get<RigidBodyComponent>(entityIdB);

        // Get the right collider to test against
        bool isCollision = false;
        switch (pRigidBodyB->shapeType)
        {
        case eShape::SPHERE:
        {
            SphereColliderComponent* pSphereB = pScene->Get<SphereColliderComponent>(entityIdB);
            isCollision = CollisionsUtils::SphereAABB_Overlap(pSphereB->radius,
                pTransformB->position,
                pTransformB->scale,
                pAABBA->min,
                pAABBA->max,
                pTransformA->position,
                pTransformA->scale);
            break;
        }
        case eShape::AABB:
        {
            AABBColliderComponent* pAABBB = pScene->Get<AABBColliderComponent>(entityIdB);
            isCollision = CollisionsUtils::AABBAABB_Overlap(pAABBA->min,
                pAABBA->max,
                pTransformA->position,
                pTransformA->scale,
                pAABBB->min,
                pAABBB->max,
                pTransformB->position,
                pTransformB->scale);
            break;
        }
        default:
            LOG_WARNING("Unknown shape for entity " + std::to_string(entityIdB));
            return false;
        }

        return isCollision;
    }
}
