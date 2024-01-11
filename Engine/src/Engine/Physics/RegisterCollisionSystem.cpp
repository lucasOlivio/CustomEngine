#include "pch.h"

#include "RegisterCollisionSystem.h"
#include "Engine/ECS/SingletonComponents/FrameCollisionLocator.h"
#include "Engine/Events/EventBusLocator.hpp"
#include "Engine/Events/CollisionEvent.h"

namespace MyEngine
{
	void RegisterCollisionSystem::Start(Scene* pScene)
	{
		// Subscribe to enter collision event
		iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

		pEventBus->Subscribe(eCollisionEvents::COLLISION_ENTER, RegisterCollision);
	}

	void RegisterCollisionSystem::Update(Scene* pScene, float deltaTime)
	{
		FrameCollisionComponent* pFrameColl = FrameCollisionLocator::Get();

		pFrameColl->collisions.clear();
	}

	void RegisterCollisionSystem::Render(Scene* pScene)
	{
	}

	void RegisterCollisionSystem::End(Scene* pScene)
	{
	}

	void RegisterCollisionSystem::RegisterCollision(const CollisionEnterEvent& event)
	{
		FrameCollisionComponent* pFrameColl = FrameCollisionLocator::Get();

		pFrameColl->collisions.push_back(event.collisionData);
	}
}
