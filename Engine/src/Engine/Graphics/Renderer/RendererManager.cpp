#include "pch.h"

#include "RendererManager.h"

#include "Engine/Utils/GraphicsUtils.h"

#include "Engine/Graphics/Materials/MaterialManagerLocator.h"
#include "Engine/Graphics/FrameBuffers/FrameBufferManagerLocator.h"

namespace MyEngine
{
	using pairFBOInfos = std::pair<uint, std::vector<sRenderModelInfo>>;
	using itFBOInfos = std::map<uint, std::vector<sRenderModelInfo>>::iterator;

	RendererManager::RendererManager()
	{
		AddFBO(0);
	}

	void RendererManager::AddFBO(uint FBOID)
	{
		m_mapRenderInfos[FBOID] = {};
		m_mapRenderInfos[FBOID].reserve(MAX_ENTITIES);
	}

	void RendererManager::AddToRender(uint FBOID, const sRenderModelInfo& renderInfo)
	{
		assert(m_mapRenderInfos.find(FBOID) != m_mapRenderInfos.end() && "FBOID not found in map!");

		m_mapRenderInfos[FBOID].push_back(renderInfo);
	}

	void RendererManager::RenderAllModels(Scene* pScene)
	{
		iMaterialManager* pMaterialManager = MaterialManagerLocator::Get();
		iFrameBufferManager* pFrameBufferManager = FrameBufferManagerLocator::Get();

		// Bind the fbo then render all their respective models
		for (const pairFBOInfos& pair : m_mapRenderInfos)
		{
			uint FBOID = pair.first;

			pFrameBufferManager->BindFBO(pScene, FBOID);

			const std::vector<sRenderModelInfo>& renderInfos = pair.second;

			// Render all models associated with the current FBOID
			for (const sRenderModelInfo& renderInfo : renderInfos)
			{
				pMaterialManager->BindMaterial(renderInfo.materialName);
				GraphicsUtils::DrawModel(renderInfo);
			}
		}

		// Making sure we return to main buffer
		pFrameBufferManager->BindFBO(pScene, 0);
	}

	void RendererManager::ClearRender()
	{
		for (itFBOInfos it = m_mapRenderInfos.begin(); it != m_mapRenderInfos.end(); ++it) 
		{
			it->second.clear();
		}
	}
}