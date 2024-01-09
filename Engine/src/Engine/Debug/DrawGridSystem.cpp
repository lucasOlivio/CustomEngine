#include "pch.h"

#include "DrawGridSystem.h"
#include "Engine/ECS/SingletonComponents/GridBroadphaseLocator.h"
#include "Engine/ECS/SingletonComponents/DebugObjectsLocator.h"
#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
	void DrawGridSystem::Start(Scene* pScene)
	{
		DebugSquareComponent* pSquare = DebugObjectsLocator::GetSquare();

		sMesh* pMesh = pSquare->pMesh;
		if (!pMesh)
		{
			LOG_WARNING("Debug Square not loaded!");
			return;
		}
	}

	void DrawGridSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void DrawGridSystem::Render(Scene* pScene)
	{
		GridBroadphaseComponent* pGrid = GridBroadphaseLocator::Get();
		DebugSquareComponent* pSquare = DebugObjectsLocator::GetSquare();

		sMesh* pMesh = pSquare->pMesh;

		for (std::pair<uint, GridAABB*> pairAABB : pGrid->mapAABBs)
		{
			GridAABB* pAABB = pairAABB.second;

			glm::mat4 matTransf = glm::mat4(1.0f);
			TransformUtils::GetTransform(pAABB->minXYZ, pGrid->lengthPerBox.x, matTransf);

			GraphicsUtils::DrawDebugModel(matTransf,
				pMesh->VAO_ID,
				pMesh->numberOfIndices,
				RED);
		}
	}

	void DrawGridSystem::End(Scene* pScene)
	{
	}
}
