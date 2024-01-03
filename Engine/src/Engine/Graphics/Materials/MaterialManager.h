#pragma once

#include "iMaterialManager.h"

namespace MyEngine
{
	class MaterialManager : public iMaterialManager
	{
	public:
		MaterialManager();
		virtual ~MaterialManager();

		virtual void BindMaterial(MaterialComponent* pMaterial);
		virtual void UnbindMaterials();

	private:
		// Textures and variables in the uniforms and units at the moment
		std::string m_currMaterial;
	};
}