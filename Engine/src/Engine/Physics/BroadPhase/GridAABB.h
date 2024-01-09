#pragma once

#include "Engine/Core/types.h"
#include "Engine/ECS/Base.h"
#include "Engine/Core/Shapes.hpp"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <math.h>
#include <unordered_set>

namespace MyEngine
{
	// Contains all triangles index (for mesh colliders) and entities inside its area
	class GridAABB : public sAABB
	{
	public:
		void RemoveStaticEntity(Entity entityID);
		void AddStaticEntity(Entity entityID);

		void RemoveNonStaticEntity(Entity entityID);
		void AddNonStaticEntity(Entity entityID);

		void AddTriangle(sTriangle* pTriangle);

		size_t NumStaticEntities();
		size_t NumNonStaticEntities();
		size_t NumTriangles();
		size_t NumTotal();

	private:
		// Any static entities collisions
		std::unordered_set<Entity> m_vecStaticEntities;

		// Any non-static entities collisions
		std::unordered_set<Entity> m_vecNonStaticEntities;

		// Collision type: Mesh collider
		// Index to mesh triangles inside this AABB
		std::unordered_set<sTriangle*> m_vecTriangles;
	};
}
