#pragma once

#include "Engine/ECS/iSystem.h"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	class CheckOverlapSystem : public iSystem
	{
	public:
		CheckOverlapSystem() = default;
		virtual ~CheckOverlapSystem() { };

		virtual void Start(Scene* pScene);

		virtual void Update(Scene* pScene, float deltaTime);

		virtual void Render(Scene* pScene);

		virtual void End(Scene* pScene);

	private:
		// Sphere checks
		void m_CheckSphereOverlaps(Scene* pScene,
								   TransformComponent* pTransformA,
								   SphereColliderComponent* pSphereA,
								   const int index,
								   const std::vector<Entity>& nonStaticEntities,
								   const std::vector<Entity>& staticEntities,
								   const std::vector<sTriangle*>& triangles);
		bool m_CheckSphereEntityOverlap(Scene* pScene,
										Entity entityIdB,
										TransformComponent* pTransformA,
										SphereColliderComponent* pSphereA);
		
		// AABB checks
		void m_CheckAABBOverlaps(Scene* pScene,
								   TransformComponent* pTransformA,
								   AABBColliderComponent* pAABBA,
								   const int index,
								   const std::vector<Entity>& nonStaticEntities,
								   const std::vector<Entity>& staticEntities,
								   const std::vector<sTriangle*>& triangles);
		bool m_CheckAABBEntityOverlap(Scene* pScene,
										Entity entityIdB,
										TransformComponent* pTransformA,
										AABBColliderComponent* pSphereA);
	};
}
