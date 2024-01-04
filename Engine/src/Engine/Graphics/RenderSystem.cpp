#include "pch.h"

#include "RenderSystem.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/SingletonComponents/CameraLocator.h"
#include "Engine/ECS/SingletonComponents/ConfigPathLocator.h"
#include "Engine/ECS/SingletonComponents/TransparentEntitiesLocator.h"
#include "Engine/Graphics/Materials/MaterialManagerLocator.h"
#include "Engine/Graphics/Textures/TextureManagerLocator.h"
#include "Engine/Graphics/Shaders/ShaderManagerLocator.h"
#include "Engine/Graphics/VAO/VAOManagerLocator.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"
#include "Engine/Utils/TransformUtils.h"
#include "Engine/Utils/GraphicsUtils.h"

namespace MyEngine
{
    void RenderSystem::Start(Scene* pScene)
    {
		ConfigPathComponent* pConfigPath = ConfigPathLocator::Get();
		iTextureManager* pTextureManager = TextureManagerLocator::Get();
		iVAOManager* pVAOManager = VAOManagerLocator::Get();
		iShaderManager* pShaderManager = ShaderManagerLocator::Get();

		// TODO: This should not be here
		// Setup shaders
		pShaderManager->SetBasePath(pConfigPath->pathShaders);
		std::string shaderName = "Shader01";
		pShaderManager->AddShaderProgram(shaderName);
		pShaderManager->UseShaderProgram(shaderName);

		// Load textures
		pTextureManager->SetBasePath(pConfigPath->pathTextures);
		for (Entity entityId : SceneView<TextureComponent>(*pScene))
		{
			TextureComponent* pTexture = pScene->Get<TextureComponent>(entityId);
			std::string errorMsg = "";
			bool isLoaded = true;

			if (pTexture->textureType == eTextureType::CUBE)
			{
				isLoaded = pTextureManager->CreateCubeTextureFromBMPFiles(pTexture->fileName,
																		  pTexture->vecTextures[0],
																		  pTexture->vecTextures[1],
																		  pTexture->vecTextures[2],
																		  pTexture->vecTextures[3],
																		  pTexture->vecTextures[4],
																		  pTexture->vecTextures[5],
																		  true,
																		  errorMsg);
				continue;
			}
			else
			{
				isLoaded = pTextureManager->Create2DTextureFromBMPFile(pTexture->fileName, true);
				errorMsg = pTextureManager->GetLastError();
			}

			if (!isLoaded)
			{
				LOG_ERROR(errorMsg);
				continue;
			}
		}

		// Load Models
		pVAOManager->SetBasePath(pConfigPath->pathModels);
		for (Entity entityId : SceneView<ModelComponent>(*pScene))
		{
			ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
			pModel->pMeshes.resize(pModel->models.size(), nullptr);
			for (int i = 0; i < pModel->models.size(); i++)
			{
				sMesh* pMesh = pVAOManager->LoadModelIntoVAO(pModel->models[i], false);
				if (!pMesh)
				{
					continue;
				}
				pModel->pMeshes[i] = pMesh;
			}
		}
    }

    void RenderSystem::Update(Scene* pScene, float deltaTime)
    {
    }

    void RenderSystem::Render(Scene* pScene)
    {
		std::vector<TransformComponent*> vecTransparentEntities;
		CameraComponent* pCamera = CameraLocator::Get();
		TransparentEntitiesComponent* pTransparents = TransparentEntitiesLocator::Get();
		iMaterialManager* pMaterialManager = MaterialManagerLocator::Get();

		// Render all "not transparent" models
		pTransparents->entities.clear();
		for (Entity entityId : SceneView<TransformComponent, ModelComponent>(*pScene))
		{
			ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);

			if (!pModel->isActive)
			{
				continue;
			}

			// Bind material
			MaterialComponent* pMaterial = pMaterialManager->GetMaterialByName(pScene, 
																			   pModel->material);
			if (pMaterial)
			{
				// Transparent objects must be rendered after
				if (pMaterial->useAlphaTexture)
				{
					pTransparents->entities.push_back(entityId);
					continue;
				}

				pMaterialManager->BindMaterial(pScene, pMaterial->name);
			}

			m_RenderModel(pTransform, pModel);
		}

		// Render all transparent models, the sorting by distance is done separatedly
		for (Entity entityId : pTransparents->entities)
		{
			ModelComponent* pModel = pScene->Get<ModelComponent>(entityId);
			TransformComponent* pTransform = pScene->Get<TransformComponent>(entityId);

			// Bind material
			MaterialComponent* pMaterial = pMaterialManager->GetMaterialByName(pScene,
																			   pModel->material);
			pMaterialManager->BindMaterial(pScene, pMaterial->name);

			m_RenderModel(pTransform, pModel);
		}
    }

    void RenderSystem::End(Scene* pScene)
    {
    }
	void RenderSystem::m_RenderModel(TransformComponent* pTransform, ModelComponent* pModel)
	{
		glm::mat4 matTransform = glm::mat4(1.0f);
		TransformUtils::GetTransform(pTransform->position,
			pTransform->orientation,
			pTransform->scale,
			matTransform);

		sMesh* pMesh = pModel->pMeshes[pModel->currMesh];
		GraphicsUtils::DrawModel(matTransform,
			pModel->isWireframe,
			pModel->doNotLight,
			pModel->useColorTexture,
			pMesh->VAO_ID,
			pMesh->numberOfIndices);
	}
}
