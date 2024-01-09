#pragma once

#include "Engine/Core/Shapes.hpp"
#include "Engine/ECS/Base.h"
#include "Engine/Graphics/opengl.h"
#include "Engine/Graphics/Textures/TextureProperties.h"
#include "Engine/Graphics/GraphicsProperties.h"
#include "Engine/Physics/BroadPhase/GridAABB.h"
#include "Engine/Utils/TransformUtils.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <map>

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

		std::string pathDebugSquare; // Path to square model inside models default folder
	};

	struct TransparentEntitiesComponent
	{
		std::vector<Entity> entities;
	};

	struct FPSCounterComponent
	{
		int frameCount = 0;
		float fpsTimer = 0.0f, currentFPS = 0.0f;
	};

	struct GridBroadphaseComponent
	{
		// Mapping of AABBs to their indices in the grid
		std::map< uint /*index*/, GridAABB* > mapAABBs;

		// Length per grid box in the grid
		glm::vec3 lengthPerBox;
	};

	// Generic grouping for any narrow phase testing 
	struct NarrowPhaseTestsComponent
	{
		// Groups of shapes and entities to test,
		// the triangles to be tested against the entities will be in the same index
		std::vector<std::vector<sTriangle*>> trianglesToTest;
		std::vector<std::vector<Entity>> staticEntitiesToTest;
		std::vector<std::vector<Entity>> nonStaticEntitiesToTest;
	};

	// Debug objects
	struct DebugSquareComponent
	{
		sMesh* pMesh;
	};
}