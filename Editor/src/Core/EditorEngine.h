#pragma once

#include "Engine/Core/Engine.h"

namespace MyEngine
{
	class Editor : public Engine
	{
	public:
		Editor() {}
		virtual ~Editor() {}

		virtual void Init(std::string initialSceneName);
	};
}
