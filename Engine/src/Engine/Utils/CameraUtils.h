#pragma once

#include <glm/glm.hpp>

namespace MyEngine
{
	class CameraUtils
	{
	public:
		glm::vec3 FinalPosition(glm::vec3 position, glm::quat orientation, 
							    float distance, float height, float offsetTarget);

		glm::mat4 ViewMat(glm::vec3 position, glm::quat orientation, 
						  float distance, float height, float offsetTarget);
	};
}
