#pragma once

#include "Engine/Core/types.h"

namespace MyEngine
{
	struct FrameBufferObject
	{
		uint ID = 0; 
		uint colorTextureId = 0;
		uint depthTextureId = 0;

		Entity cameraId = 0;

		int width = 1;
		int height = 1;
	};
}
