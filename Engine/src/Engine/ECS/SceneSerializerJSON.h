#pragma once

#include "iSceneSerializer.h"
#include "Engine/ECS/Components.h"
#include <rapidjson/document.h>

namespace MyEngine
{
	class SceneSerializerJSON : public iSceneSerializer
	{
	public:
		SceneSerializerJSON();
		virtual ~SceneSerializerJSON();

		virtual bool DeserializeScene(const std::string& filePath, Scene& sceneOut);

		virtual bool SerializeScene(const std::string& filePath, Scene& sceneIn);

	private:
		rapidjson::Document m_doc;

		bool m_LoadDoc(const std::string& filePath);
		bool m_SaveDoc(const std::string& filePath);

		// Parse values from doc to the respective data structure
		bool m_ParseSceneToDoc(Scene& sceneIn);
		bool m_ParseTagToDoc(rapidjson::Value& jsonObject, TagComponent& tagIn);
		bool m_ParseTransformToDoc(rapidjson::Value& jsonObject, TransformComponent& transformIn);
		bool m_ParseMovementToDoc(rapidjson::Value& jsonObject, MovementComponent& movementIn);

		// Parse values From the respective data structures into the doc
		bool m_ParseDocToScene(Scene& sceneOut);
		bool m_ParseDocToTag(rapidjson::Value& jsonObject, TagComponent& tagOut);
		bool m_ParseDocToTransform(rapidjson::Value& jsonObject, TransformComponent& transformOut);
		bool m_ParseDocToMovement(rapidjson::Value& jsonObject, MovementComponent& movementOut);
	};
}