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
        iVAOManager* pVAOManager = VAOManagerLocator::Get();

        DebugSquareComponent* pSquare = DebugObjectsLocator::GetSquare();
        DebugSphereComponent* pSphere = DebugObjectsLocator::GetSphere();

        pSquare->pMesh = pVAOManager->LoadModelIntoVAO(pConfigPath->pathDebugSquare, true);
        pSphere->pMesh = pVAOManager->LoadModelIntoVAO(pConfigPath->pathDebugSphere, true);
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
