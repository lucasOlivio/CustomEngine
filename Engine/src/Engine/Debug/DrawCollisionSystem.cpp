#include "pch.h"

#include "DrawCollisionSystem.h"

#include "Engine/ECS/SingletonComponents/DebugObjectsLocator.h"
#include "Engine/ECS/SingletonComponents/FrameCollisionLocator.h"
#include "Engine/ECS/SingletonComponents/FrameCounterLocator.h"

#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
	void DrawCollisionSystem::Start(Scene* pScene)
	{
	}

	void DrawCollisionSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void DrawCollisionSystem::Render(Scene* pScene)
	{
		FrameCounterComponent* pFrames = FrameCounterLocator::Get();
		FrameCollisionComponent* pFrameColl = FrameCollisionLocator::Get();
		DebugSphereComponent* pSphere = DebugObjectsLocator::GetSphere();
		sMesh* pMesh = pSphere->pMesh;

		int currFrame = pFrames->frameCount % FRAME_RATE;
		const std::vector<sCollisionData>& currFrameColls = pFrameColl->collisions[currFrame];
		// Draw a wireframe blue sphere at the contact points
		for (const sCollisionData& coll : currFrameColls)
		{
			glm::mat4 matTransf = glm::mat4(1.0f);
			TransformUtils::GetTransform(coll.contactPoint, 1.0f, matTransf);

			GraphicsUtils::DrawDebugModel(matTransf,
										  pMesh->VAO_ID,
										  pMesh->numberOfIndices,
										  BLUE);
		}
	}

	void DrawCollisionSystem::End(Scene* pScene)
	{
	}
}
