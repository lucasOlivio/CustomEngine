#include "pch.h"

#include "MaterialManager.h"
#include "Engine/Graphics/Shaders/ShaderManager.h"
#include "Engine/Graphics/Textures/TextureManagerLocator.h"

namespace MyEngine
{
	MaterialManager::MaterialManager()
	{}

	MaterialManager::~MaterialManager()
	{
	}

	void MaterialManager::BindMaterial(MaterialComponent* pMaterial)
	{
		// Only change material if not already binded
		if (pMaterial->materialName == m_currMaterial)
		{
			return;
		}

		UnbindMaterials();
		std::vector<TextureComponent*> vecTexturesComp = pMaterial->texturesComponents;

		iShaderProgram* pShader = ShaderManager::GetActiveShader();
		iTextureManager* pTextureManager = TextureManagerLocator::Get();

		// Update offset, alpha and if is emissive material
		// TODO: Regulate the intensity of the emissiviness
		pShader->SetUniformInt("isEmissive", pMaterial->isEmissive);

		glm::vec3 finaloffset = pMaterial->currOffset + pMaterial->offset;
		pShader->SetUniformVec2("UVOffset", finaloffset);

		pShader->SetUniformVec2("HeightMapOffset", pMaterial->currOffsetHeightMap);

		// Bind color textures
		for (int i = 0; i < pMaterial->colorTextures.size(); i++)
		{
			pTextureManager->BindTexture(vecTexturesComp[i]->fileName,
				vecTexturesComp[i]->textureType,
				pMaterial->colorTexturesRatios[i]);
		}

		// TODO: Remove repetition, all could be in a vector or map
		// Bind heightmap textures
		if (pMaterial->useHeightMap)
		{
			// Height scale can be passed as the "ratio parameter", will be placed on the heightscale uniform
			pTextureManager->BindTexture(pMaterial->heightMapTexture,
				eTextureType::HEIGHTMAP,
				pMaterial->heightScale);
		}

		// Bind normal textures
		if (pMaterial->useNormalTexture)
		{
			pTextureManager->BindTexture(pMaterial->normalTexture,
				eTextureType::NORMAL,
				0);
		}

		// Bind specular textures
		if (pMaterial->useSpecularTexture)
		{
			pTextureManager->BindTexture(pMaterial->specularTexture,
				eTextureType::SPECULAR,
				0);
		}

		// Bind discard textures
		if (pMaterial->useDiscardTexture)
		{
			pTextureManager->BindTexture(pMaterial->discardTexture,
				eTextureType::DISCARD,
				0);
		}

		// Bind alpha textures
		if (pMaterial->useAlphaTexture)
		{
			pTextureManager->BindTexture(pMaterial->alphaTexture,
				eTextureType::TRANSPARENCY,
				0);
		}

		// Bind cube textures
		if (pMaterial->useCubeTexture)
		{
			pTextureManager->BindTexture(pMaterial->cubeTexture,
										   eTextureType::CUBE,
										   0);
		}

		m_currMaterial = pMaterial->materialName;
	}

	void MaterialManager::UnbindMaterials()
	{
		iShaderProgram* pShader = ShaderManager::GetActiveShader();
		iTextureManager* pTextureManager = TextureManagerLocator::Get();

		pTextureManager->ResetSamplers();
		pShader->SetUniformVec2("UVOffset", glm::vec2(0.0, 0.0));
		pShader->SetUniformVec2("HeightMapOffset", glm::vec2(0.0, 0.0));
		pShader->SetUniformInt("isEmissive", false);
	}
}
