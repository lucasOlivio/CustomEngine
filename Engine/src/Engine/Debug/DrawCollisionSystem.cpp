#include "pch.h"

#include "DrawCollisionSystem.h"
#include "Engine/ECS/SingletonComponents/DebugObjectsLocator.h"
#include "Engine/Events/EventBusLocator.hpp"
#include "Engine/Events/CollisionEvent.h"
#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
	void DrawCollisionSystem::Start(Scene* pScene)
	{
		// Just a check if the debug sphere mesh loaded
		DebugSphereComponent* pSphere = DebugObjectsLocator::GetSphere();

		sMesh* pMesh = pSphere->pMesh;
		if (!pMesh)
		{
			LOG_WARNING("Debug Sphere not loaded!");
			return;
		}

		// Subscribe to collision event
		iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

		pEventBus->Subscribe(eCollisionEvents::COLLISION_ENTER, DrawCollision);
	}

	void DrawCollisionSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void DrawCollisionSystem::Render(Scene* pScene)
	{
	}

	void DrawCollisionSystem::End(Scene* pScene)
	{
	}

	void DrawCollisionSystem::DrawCollision(const CollisionEnterEvent& event)
	{
		DebugSphereComponent* pSphere = DebugObjectsLocator::GetSphere();
		sMesh* pMesh = pSphere->pMesh;

		// Draw a wireframe blue sphere at the contact point
		glm::mat4 matTransf = glm::mat4(1.0f);
		TransformUtils::GetTransform(event.collisionData.contactPoint, 2.0f, matTransf);

		GraphicsUtils::DrawDebugModel(matTransf,
									  pMesh->VAO_ID,
									  pMesh->numberOfIndices,
									  BLUE);
	}
}
