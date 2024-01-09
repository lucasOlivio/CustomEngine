#include "pch.h"

#include "DebugSystem.h"
#include "Engine/ECS/SingletonComponents/DebugObjectsLocator.h"
#include "Engine/ECS/SingletonComponents/ConfigPathLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"

namespace MyEngine
{
    void DebugSystem::Start(Scene* pScene)
    {
        ConfigPathComponent* pConfigPath = ConfigPathLocator::Get();
        DebugSquareComponent* pSquare = DebugObjectsLocator::GetSquare();
        iVAOManager* pVAOManager = VAOManagerLocator::Get();

        pSquare->pMesh = pVAOManager->LoadModelIntoVAO(pConfigPath->pathDebugSquare, true);
    }

    void DebugSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void DebugSystem::Render(Scene* pScene)
    {
    }

    void DebugSystem::End(Scene* pScene)
    {
    }
}
