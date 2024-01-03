#include "pch.h"

#include "LightSystem.h"
#include "Engine/ECS/SceneView.hpp"

namespace MyEngine
{
    LightSystem::LightSystem()
    {
    }

    LightSystem::~LightSystem()
    {
    }

    void LightSystem::Start(Scene* pScene)
    {
        // Go over each lights setting the ULs and initializing them
        int lightIndex = 0;
        for (Entity entityId : SceneView<TransformComponent, LightComponent>(*pScene))
        {
            LightComponent* pLight = pScene->Get<LightComponent>(entityId);
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);

            m_SetupLight(pTransform, pLight, lightIndex);
            lightIndex++;
        }
    }

    void LightSystem::Update(Scene* pScene, float deltaTime)
    {
        iShaderProgram* pShader = ShaderManager::GetActiveShader();

        // Set lights to transform position of entity
        for (Entity entityId : SceneView<TransformComponent, LightComponent>(*pScene))
        {
            LightComponent* pLight = pScene->Get<LightComponent>(entityId);
            TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);

            m_UpdateDirectionUL(pLight, pShader);
            m_UpdatePositionUL(pTransform, pLight, pShader);
            m_UpdateAttenUL(pLight, pShader);
        }
    }

    void LightSystem::m_SetupLight(TransformComponent* pTransform, 
                                   LightComponent* pLight, int lightIndex)
    {
        std::string ulBasePath = "theLights[" + std::to_string(lightIndex) + "].";
        iShaderProgram* pShader = ShaderManager::GetActiveShader();

        pLight->ulBasePath = ulBasePath;

        // Initial update in uniforms
        m_UpdatePositionUL(pTransform, pLight, pShader);
        m_UpdateDirectionUL(pLight, pShader);
        m_UpdateDiffuseUL(pLight, pShader);
        m_UpdateSpecularUL(pLight, pShader);
        m_UpdateAttenUL(pLight, pShader);
        m_UpdateParamsUL(pLight, pShader);
        m_UpdateStatusUL(pLight, pShader);
    }

    void LightSystem::m_UpdatePositionUL(TransformComponent* pTransform, 
                                         LightComponent* pLight, 
                                         iShaderProgram* pShader)
    {
        glm::vec4 newPosition = glm::vec4(pTransform->position, 0) + pLight->positionOffset +
                               (pLight->direction * pLight->directionOffset);

        pShader->SetUniformVec4((pLight->ulBasePath + "position").c_str(), newPosition);
    }

    void LightSystem::m_UpdateDirectionUL(LightComponent* pLight, iShaderProgram* pShader)
    {
        glm::vec4 newDirection = pLight->direction + pLight->directionOffset;
        pShader->SetUniformVec4((pLight->ulBasePath + "direction").c_str(), newDirection);
    }

    void LightSystem::m_UpdateDiffuseUL(LightComponent* pLight, iShaderProgram* pShader)
    {
        pShader->SetUniformVec4((pLight->ulBasePath + "diffuse").c_str(), pLight->diffuse);
    }

    void LightSystem::m_UpdateSpecularUL(LightComponent* pLight, iShaderProgram* pShader)
    {
        pShader->SetUniformVec4((pLight->ulBasePath + "specular").c_str(), pLight->specular);
    }

    void LightSystem::m_UpdateAttenUL(LightComponent* pLight, iShaderProgram* pShader)
    {
        pShader->SetUniformVec4((pLight->ulBasePath + "atten").c_str(), pLight->atten);
    }

    void LightSystem::m_UpdateParamsUL(LightComponent* pLight, iShaderProgram* pShader)
    {
        pShader->SetUniformVec4((pLight->ulBasePath + "params").c_str(), pLight->params);
    }

    void LightSystem::m_UpdateStatusUL(LightComponent* pLight, iShaderProgram* pShader)
    {
        pShader->SetUniformInt((pLight->ulBasePath + "status").c_str(), pLight->status);
    }
}
