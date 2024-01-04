#pragma once

#include "Engine/ECS/Base.h"
#include "Engine/Graphics/Textures/TextureProperties.h"
#include "Engine/Utils/TransformUtils.h"
#include "Engine/Graphics/opengl.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>

namespace MyEngine
{
	// Singleton components
	struct CameraComponent
	{
		glm::vec3 position;
		glm::quat orientation;
		glm::vec3 upVector;
		float distance;
		float height;
		float offsetTarget;

		glm::vec3 FinalPosition()
		{
			using namespace glm;

			vec3 transfUp = TransformUtils::GetUpVector(orientation);
			vec3 transfForward = TransformUtils::GetForwardVector(orientation);

			vec3 offsetDist = -distance * transfForward;
			vec3 offsetHeight = height * transfUp;

			vec3 camFinalPos = position + offsetDist + offsetHeight;

			return camFinalPos;
		}

		glm::mat4 ViewMat()
		{
			using namespace glm;

			// Calculating camera view
			vec3 cameraPosition = FinalPosition();

			vec3 target = position + (TransformUtils::GetForwardVector(orientation) * offsetTarget);

			return lookAt(
				cameraPosition,
				target,
				TransformUtils::GetUpVector(orientation)
			);
		}
	};

	struct WindowComponent
	{
		std::string name;
		int width;
		int height;
		float zNear;
		float zFar;
		float fovy;

		GLFWwindow* pGLFWWindow;

		float Ratio()
		{
			float ratio = 0.0f;
			if (height > 0)
			{
				ratio = width / (float)height;
			}

			return ratio;
		}

		glm::mat4 ProjectionMat()
		{
			return glm::perspective(fovy,
								    Ratio(),
								    zNear,
								    zFar);
		}
	};

	struct ConfigPathComponent
	{
		std::string pathModels;
		std::string pathAudio;
		std::string pathShaders;
		std::string pathScripts;
		std::string pathTextures;
	};

	struct TransparentEntitiesComponent
	{
		std::vector<Entity> entities;
	};
}