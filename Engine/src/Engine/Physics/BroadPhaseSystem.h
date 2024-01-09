#pragma once

#include "Engine/ECS/iSystem.h"
#include "Engine/ECS/Components.h"
#include "Engine/Core/Shapes.hpp"
#include "Engine/Physics/PhysicsProperties.h"
#include "GridAABB.h"
#include <map>

namespace MyEngine
{
	typedef std::map< uint /*index*/, GridAABB* > mapIdxAABB;
	typedef std::map< uint /*index*/, GridAABB* > mapIdxAABB;
	typedef std::unordered_set< Entity >::iterator itEntities;

	class BroadPhaseSystem : public iSystem
	{
	public:
		BroadPhaseSystem() = default;
		virtual ~BroadPhaseSystem() {};

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

	protected:
		// All AABBs and its index localization
		mapIdxAABB m_mapAABBs;
		// Only AABBs that have non-static entities
		// Used for keeping track of which aabb really need testing
		mapIdxAABB m_mapActiveAABBs;

		glm::vec3 m_lengthPerBox;

		GridAABB* m_GetAABB(uint idxAABB);
		GridAABB* m_GetAABB(glm::vec3 point);

		GridAABB* m_GetOrCreateAABB(uint idxAABB);

		// Calculates all the aabbs that the shape intersects
		// and inserts into the respective Grid AABB
		void m_InsertAABB(Scene* pScene, Entity entityId, eBody bodyType);
		void m_InsertSphere(Scene* pScene, Entity entityId, eBody bodyType);
		void m_InsertMeshTriangle(Entity entityId, sTriangle* pTriangle);
		void m_InsertMesh(Scene* pScene, Entity entityId, eBody bodyType);

		// Insert entity in map and active map if not a static body
		void m_InsertEntity(Entity entityID, uint index, eBody bodyType);

		// Remove AABB from mapping of actives
		size_t m_RemoveActiveAABB(uint idxAABB);

		// Remove entity from aabb and map and active map if not static body
		void m_RemoveEntityAABB(Entity entityID, uint index, eBody bodyType);

		// Remove AABB from mapping if exists
		size_t m_RemoveAABB(uint idxAABB);

		void m_ClearAABBs();
	};
}
