#include "pch.h"

#include "TextureSystem.h"
#include "TextureManagerLocator.h"
#include "Engine/ECS/SceneView.hpp"
#include "Engine/ECS/Components.h"

namespace MyEngine
{
	void TextureSystem::Start(Scene* pScene)
	{
		iTextureManager* pTextureManager = TextureManagerLocator::Get();

		// Bind texture component
		for (Entity entityId : SceneView<TextureComponent>(*pScene))
		{
			TextureComponent* pTexture = pScene->Get<TextureComponent>(entityId);

			bool isLoaded;
			std::string errorMsg = "";
			if (pTexture->textureType == eTextureType::CUBE)
			{
				if (pTexture->vecTextures.size() < 6)
				{
					std::string error = "Cube Texture " + pTexture->fileName + 
						" don't have enough sides";
					LOG_ERROR(error);
					continue;
				}
				// Load all sides from bitmap files
				isLoaded = pTextureManager->CreateCubeTextureFromBMPFiles(pTexture->fileName,
					pTexture->vecTextures[0],
					pTexture->vecTextures[1],
					pTexture->vecTextures[2],
					pTexture->vecTextures[3],
					pTexture->vecTextures[4],
					pTexture->vecTextures[5],
					true,
					errorMsg);
			}
			else
			{
				// Load texture bitmap from file
				isLoaded = pTextureManager->Create2DTextureFromBMPFile(pTexture->fileName, true);
				errorMsg = pTextureManager->GetLastError();
			}

			if (!isLoaded)
			{
				LOG_ERROR(errorMsg);
				return;
			}
		}
	}

	void TextureSystem::Update(Scene* pScene, float deltaTime)
	{
	}

	void TextureSystem::Render(Scene* pScene)
	{
	}

	void TextureSystem::End(Scene* pScene)
	{
	}
}
