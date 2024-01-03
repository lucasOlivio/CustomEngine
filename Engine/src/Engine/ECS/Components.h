#pragma once

#include "Base.h"
#include "Engine/Graphics/Textures/TextureProperties.h"
#include <glm/gtc/quaternion.hpp>

namespace MyEngine
{
	struct TagComponent
	{
		std::string name;
	};

	struct TransformComponent
	{
		glm::vec3 position;
		glm::quat orientation;
		float scale;
	};

	struct MovementComponent
	{
		glm::vec3 velocity;
		glm::vec3 acceleration;
	};

	struct TextureComponent
	{
		std::string fileName;
		eTextureType textureType;

		// Cube map list of texture sides
		std::vector<std::string> vecTextures;
	};

	struct MaterialComponent
	{
		std::string materialName;

		glm::vec3 offset; // fixed offset

		glm::vec3 currOffset;
		glm::vec3 offsetMove;

		glm::vec3 currOffsetHeightMap;
		glm::vec3 offsetHeightMap;

		std::vector<std::string> colorTextures;
		glm::vec3 colorTexturesRatios;

		bool useHeightMap;
		std::string heightMapTexture;
		float heightScale;

		bool useNormalTexture;
		std::string normalTexture;

		bool useSpecularTexture;
		std::string specularTexture;

		bool useDiscardTexture;
		std::string discardTexture;

		bool useCubeTexture;
		std::string cubeTexture;

		bool isEmissive;

		// Material transparency
		bool useAlphaTexture;
		std::string alphaTexture;

		std::vector<TextureComponent*> texturesComponents;
	};

	// Singleton components


}
