#include "pch.h"

#include "CameraSystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/CameraLocator.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"

namespace MyEngine
{
    void CameraSystem::Start(Scene* pScene)
    {
    }

    void CameraSystem::Update(Scene* pScene, float deltaTime)
    {
        // Updating camera view
        CameraComponent* pCamera = CameraLocator::Get();
        iShaderProgram* pShader = ShaderManager::GetActiveShader();

        glm::mat4 matView = pCamera->ViewMat();
        pShader->SetUniformMatrix4f("matView", matView);
    }

    void CameraSystem::Render(Scene* pScene)
    {
    }

    void CameraSystem::End(Scene* pScene)
    {
    }
}
