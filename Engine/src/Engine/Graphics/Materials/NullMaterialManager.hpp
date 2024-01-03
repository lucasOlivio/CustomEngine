#pragma once

#include "pch.h"
#include "iMaterialManager.h"

namespace MyEngine
{
	class NullMaterialManager : public iMaterialManager
	{
	public:
		NullMaterialManager() {};
		virtual ~NullMaterialManager() {};

		virtual void BindMaterial(MaterialComponent* pMaterial)
		{
			LOG_ERROR("MaterialManager not set!");
		}

		virtual void UnbindMaterials()
		{
			LOG_ERROR("MaterialManager not set!");
		}
	};
}