#include "pch.h"

#include "BroadPhaseSystem.h"
#include "Engine/ECS/Components.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/Utils/GridUtils.h"
#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/CollisionsUtils.h"

namespace MyEngine
{
	typedef std::map< uint /*index*/, GridAABB* >::iterator itIdxAABB;
	typedef std::pair< uint /*index*/, GridAABB* > pairIdxAABB;

	void BroadPhaseSystem::Start(Scene* pScene)
	{
		// TODO: For non-static grid aabbs this should be dynamic, comming from component size or map
		m_lengthPerBox = glm::vec3(5, 5, 5);


		for (Entity entityId : SceneView<TransformComponent, RigidBodyComponent>(*pScene))
		{
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);
			RigidBodyComponent* pRigidBody = pScene->Get<RigidBodyComponent>(entityId);

			uint idxpos = GridUtils::LocatePoint(pTransform->worldPosition, m_lengthPerBox);
			m_InsertEntity(entityId, idxpos, pRigidBody->bodyType);

			switch (pRigidBody->shapeType)
			{
			case eShape::AABB:
				m_InsertAABB(pScene, entityId, pRigidBody->bodyType);
				break;
			case eShape::SPHERE:
				m_InsertSphere(pScene, entityId, pRigidBody->bodyType);
				break;
			case eShape::MESH_OF_TRIANGLES:
				m_InsertMesh(pScene, entityId, pRigidBody->bodyType);
				break;
			default:
				break;
			}
		}
	}

	void BroadPhaseSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void BroadPhaseSystem::Render(Scene* pScene)
	{
	}

	void BroadPhaseSystem::End(Scene* pScene)
	{
		m_ClearAABBs();
	}

	GridAABB* BroadPhaseSystem::m_GetAABB(uint idxAABB)
	{
		itIdxAABB itAABB = m_mapAABBs.find(idxAABB);
		if (itAABB == m_mapAABBs.end())
		{
			return nullptr;
		}

		return itAABB->second;
	}

	GridAABB* BroadPhaseSystem::m_GetAABB(glm::vec3 point)
	{
		uint idxAABB = GridUtils::LocatePoint(point, m_lengthPerBox);

		return m_GetAABB(idxAABB);
	}

	GridAABB* BroadPhaseSystem::m_GetOrCreateAABB(uint idxAABB)
	{
		GridAABB* pAABB = m_GetAABB(idxAABB);
		if (pAABB)
		{
			return pAABB;
		}

		pAABB = new GridAABB();
		pAABB->minXYZ = GridUtils::LocatePosition(idxAABB, m_lengthPerBox);
		pAABB->maxXYZ = pAABB->minXYZ + m_lengthPerBox;

		m_mapAABBs[idxAABB] = pAABB;

		return pAABB;
	}

	void BroadPhaseSystem::m_InsertAABB(Scene* pScene, Entity entityId, eBody bodyType)
	{
		AABBColliderComponent* pAABB = pScene->Get<AABBColliderComponent>(entityId);
		if (!pAABB)
		{
			return;
		}
	}

	void BroadPhaseSystem::m_InsertSphere(Scene* pScene, Entity entityId, eBody bodyType)
	{
		SphereColliderComponent* pSphere = pScene->Get<SphereColliderComponent>(entityId);
		if (!pSphere)
		{
			return;
		}

		//// Check collisions in the neighboring cells

		//// Calculate the number of neighboring cells to check based on the sphere radius
		//int numNeighborsX = (int)(ceil(pSphere->radius / m_lengthPerBox.x));
		//int numNeighborsY = (int)(ceil(pSphere->radius / m_lengthPerBox.y));
		//int numNeighborsZ = (int)(ceil(pSphere->radius / m_lengthPerBox.z));

		//glm::vec3 posCell = GridUtils::LocatePosition(idxpos, m_lengthPerBox);
		//for (int i = -numNeighborsX; i <= numNeighborsX; ++i) 
		//{
		//	float radiusI = pSphere->radius / i;
		//	for (int j = -numNeighborsY; j <= numNeighborsY; ++j) 
		//	{
		//		float radiusJ = pSphere->radius / j;
		//		for (int k = -numNeighborsZ; k <= numNeighborsZ; ++k) 
		//		{
		//			float radiusK = pSphere->radius / k;

		//			// Proportional radius that would be in neighbor cell
		//			glm::vec3 currRadius = glm::vec3(radiusI, radiusJ, radiusK);
		//			glm::vec3 currPoint = pTransform->worldPosition + currRadius;

		//			uint currIdxpos = GridUtils::LocatePoint(currPoint, m_lengthPerBox);

		//			if (idxpos == currIdxpos)
		//			{
		//				// Still in the same grid
		//				continue;
		//			}

		//			// Different grid, insert entity in it too
		//			m_InsertEntity(entityId, currIdxpos, bodyType);
		//		}
		//	}
		//}
	}

	void BroadPhaseSystem::m_InsertMesh(Scene* pScene, Entity entityId, eBody bodyType)
	{
		MeshColliderComponent* pMeshCollider = pScene->Get<MeshColliderComponent>(entityId);
		sMesh* pMesh = pMeshCollider->pMesh;
		if (!pMeshCollider || !pMeshCollider->pMesh)
		{
			return;
		}

		// for every triangle in the mesh insert into aabb
		for (uint i = 0; i < pMesh->numberOfTriangles; i++)
		{
			m_InsertMeshTriangle(entityId, &(pMesh->pTriangles[i]));
		}
	}

	void BroadPhaseSystem::m_InsertEntity(Entity entityID, uint index, eBody bodyType)
	{
		GridAABB* pAABB = m_GetOrCreateAABB(index);

		if (bodyType == eBody::STATIC)
		{
			pAABB->AddStaticEntity(entityID);
			return;
		}

		pAABB->AddNonStaticEntity(entityID);

		// If first entity inserted then we can set aabb to actives
		if (pAABB->NumNonStaticEntities() == 1)
		{
			m_mapActiveAABBs[index] = pAABB;
		}

		return;
	}

	void BroadPhaseSystem::m_InsertMeshTriangle(Entity entityId, sTriangle* pTriangle)
	{
		pTriangle->calcNormal();

		// Locate each vertex
		uint idxV1 = GridUtils::LocatePoint(pTriangle->vertices[0], m_lengthPerBox);
		uint idxV2 = GridUtils::LocatePoint(pTriangle->vertices[0], m_lengthPerBox);
		uint idxV3 = GridUtils::LocatePoint(pTriangle->vertices[0], m_lengthPerBox);

		// TODO: When a pTriangle edge passes 3 or more aabbs it should be in those aabbs too
		// Insert pTriangle into all AABBs that it intersects
		GridAABB* pAABB = m_GetOrCreateAABB(idxV1);
		pAABB->AddTriangle(pTriangle);

		if (idxV2 != idxV1)
		{
			GridAABB* pAABB2 = m_GetOrCreateAABB(idxV2);
			pAABB->AddTriangle(pTriangle);
		}

		if (idxV3 != idxV1 && idxV3 != idxV2)
		{
			GridAABB* pAABB3 = m_GetOrCreateAABB(idxV3);
			pAABB->AddTriangle(pTriangle);
		}

		return;
	}

	void BroadPhaseSystem::m_ClearAABBs()
	{
		for (pairIdxAABB pairAABB : m_mapAABBs)
		{
			delete pairAABB.second;
		}

		m_mapAABBs.clear();
		m_mapActiveAABBs.clear();
	}

	size_t BroadPhaseSystem::m_RemoveActiveAABB(uint idxAABB)
	{
		GridAABB* pAABB = m_GetAABB(idxAABB);
		if (!pAABB)
		{
			return 0;
		}

		size_t left = m_mapActiveAABBs.erase(idxAABB);

		return left;
	}

	void BroadPhaseSystem::m_RemoveEntityAABB(Entity entityID, uint index, eBody bodyType)
	{
		GridAABB* pAABB = m_GetAABB(index);
		if (!pAABB)
		{
			return;
		}

		if (bodyType == eBody::STATIC)
		{
			pAABB->RemoveStaticEntity(entityID);
		}
		else
		{
			pAABB->RemoveNonStaticEntity(entityID);
		}

		// remove AABB from active if no entities left
		if (pAABB->NumNonStaticEntities() == 0)
		{
			m_RemoveActiveAABB(index);
		}
	}

	size_t BroadPhaseSystem::m_RemoveAABB(uint idxAABB)
	{
		GridAABB* pAABB = m_GetAABB(idxAABB);
		if (!pAABB)
		{
			return 0;
		}

		size_t left = m_mapAABBs.erase(idxAABB);
		delete pAABB;

		return left;
	}
}
