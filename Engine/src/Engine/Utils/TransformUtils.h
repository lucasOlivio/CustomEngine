#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace MyEngine
{
	class TransformUtils
	{
	public:
        static void ApplyTranslation(glm::vec3 position, glm::mat4& matModelOut);

        static void ApplyRotation(glm::quat qOrientation, glm::mat4& matModelOut);

		static void ApplyScale(float scale, glm::mat4& matModelOut);

		static void GetTransform(glm::vec3 position, 
                                 glm::quat orientation,
                                 float scale, 
                                 glm::mat4& matModelOut);

		static glm::vec3 GetUpVector(glm::quat orientation);
		static glm::vec3 GetForwardVector(glm::quat orientation);
	};
}
