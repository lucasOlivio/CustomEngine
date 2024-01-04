#pragma once

#include <glm/mat4x4.hpp>

namespace MyEngine
{
	class GraphicsUtils
	{
	public:
		// Sets all needed uniforms and draw model using VAO and opengl
		static void DrawModel(glm::mat4 matModel,
							  bool isWireFrame,
							  bool doNotLight,
							  bool useColorTexture,
							  int VAO_ID,
							  int numberOfIndices);

		static void DrawTiledModel(glm::vec3 axis,
								   glm::vec3 offset,
								   glm::mat4 matModel,
								   bool isWireFrame,
								   bool doNotLight,
								   bool useColorTexture,
								   int VAO_ID,
								   int numberOfIndices);
	};
}
