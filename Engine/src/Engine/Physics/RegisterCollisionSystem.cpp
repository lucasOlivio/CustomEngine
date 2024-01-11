#include "pch.h"

#include "RegisterCollisionSystem.h"

#include "Engine/ECS/SingletonComponents/FrameCollisionLocator.h"
#include "Engine/ECS/SingletonComponents/FrameCounterLocator.h"

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
		FrameCounterComponent* pFrames = FrameCounterLocator::Get();

		// Module to make sure we stay in FRAME_RATE size
		int currFrame = pFrames->frameCount % FRAME_RATE;
		pFrameColl->collisions[currFrame].clear();
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
		FrameCounterComponent* pFrames = FrameCounterLocator::Get();

		// Module to make sure we stay in FRAME_RATE size
		int currFrame = pFrames->frameCount % FRAME_RATE;
		pFrameColl->collisions[currFrame].push_back(event.collisionData);
	}
}
