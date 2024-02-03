#include "pch.h"

#include "CameraSystem.h"

#include "Engine/ECS/Scene/SceneView.hpp"
#include "Engine/ECS/Components.h"

#include "Engine/Graphics/Shaders/ShaderManager.h"

#include "Engine/Utils/CameraUtils.h"

namespace MyEngine
{
    void CameraSystem::Init()
    {
    }

    void CameraSystem::Start(Scene* pScene)
    {
    }

    void CameraSystem::Update(Scene* pScene, float deltaTime)
    {
        // Updating camera view (Main screen camera only)
        Entity cameraId = CameraUtils::GetMainCamera(pScene);

        CameraComponent* pCamera = pScene->Get<CameraComponent>(cameraId);
        TransformComponent* pTransform = pScene->Get<TransformComponent>(cameraId);
        iShaderProgram* pShader = ShaderManager::GetActiveShader();

        glm::mat4 matView = CameraUtils::ViewMat(pTransform->position, pTransform->orientation,
                                                 pCamera->distance, pCamera->height, pCamera->offsetTarget);
        pShader->SetUniformMatrix4f("matView", matView);
    }

    void CameraSystem::Render(Scene* pScene)
    {
    }

    void CameraSystem::End(Scene* pScene)
    {
    }

    void CameraSystem::Shutdown()
    {
    }
}
