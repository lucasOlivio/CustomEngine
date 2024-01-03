#pragma once

#include "Engine/ECS/Components.h"

namespace MyEngine
{
	class iMaterialManager
	{
	public:
		iMaterialManager() {};
		virtual ~iMaterialManager() {};

		virtual void BindMaterial(MaterialComponent* pMaterial) = 0;
		virtual void UnbindMaterials() = 0;
	};
}