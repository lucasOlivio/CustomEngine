#include "pch.h"

#include "SceneSerializerJSON.h"
#include "Engine/Utils/ParserJSON.h"

#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>

namespace MyEngine
{
    SceneSerializerJSON::SceneSerializerJSON()
    {
        m_doc.SetObject();
    }

    SceneSerializerJSON::~SceneSerializerJSON()
    {
    }

    bool SceneSerializerJSON::DeserializeScene(const std::string& filePath, Scene& sceneOut)
    {
        bool isLoaded = m_LoadDoc(filePath);
        if (!isLoaded)
        {
            return false;
        }

        // Parse scene json and load into object
        bool isParsed = m_ParseDocToScene(sceneOut);
        if (!isParsed)
        {
            std::string errorMsg = "Error parsing file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        m_doc.Clear();

        return true;
    }

    bool SceneSerializerJSON::SerializeScene(const std::string& filePath, Scene& sceneIn)
    {
        // Convert the scene object to a JSON document
        bool isParsed = m_ParseSceneToDoc(sceneIn);
        if (!isParsed)
        {
            std::string errorMsg = "Error parsing doc to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        bool isSaved = m_SaveDoc(filePath);

        if (!isSaved) {
            std::string errorMsg = "Error saving json to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        m_doc.Clear();

        return true;
    }

    bool SceneSerializerJSON::m_LoadDoc(const std::string& filePath)
    {
        using namespace rapidjson;

        // Load file stream into document object
        FILE* fp = 0;
        fopen_s(&fp, filePath.c_str(), "rb");

        if (!fp)
        {
            std::string errorMsg = "File '" + filePath + "' not found!";
            LOG_ERROR(errorMsg);
            return false;
        }

        char readBuffer[MAX_LINE_LENGTH];
        FileReadStream fs(fp, readBuffer, sizeof(readBuffer));

        m_doc.ParseStream(fs);

        fclose(fp);

        std::string infoMsg = "File '" + filePath + "' loaded!";
        LOG_INFO(infoMsg);

        return true;
    }

    bool SceneSerializerJSON::m_SaveDoc(const std::string& filePath)
    {
        using namespace rapidjson;

        StringBuffer buf;
        PrettyWriter<StringBuffer> writer(buf);

        m_doc.Accept(writer);

        // Get the JSON string from the buffer
        std::string json = buf.GetString();

        // Write the JSON to a file
        std::ofstream of(filePath, std::ios::out | std::ios::trunc);
        of << json;

        if (!of.good()) {
            std::string errorMsg = "Error saving json to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        of.close();

        return true;
    }

    bool SceneSerializerJSON::m_ParseSceneToDoc(Scene& sceneIn)
    {
        using namespace rapidjson;

        Document::AllocatorType& allocator = m_doc.GetAllocator();
        m_doc.SetArray();

        // Parse and serialize each entity in the scene
        EntityManager* pEntityManager = sceneIn.GetEntitymanager();
        for (const Entity& entity : pEntityManager->GetEntities())
        {
            // Create a JSON object for each entity
            Value entityObject;
            entityObject.SetObject();

            // Create a RapidJSON object for each component
            if (pEntityManager->HasComponent(entity, sceneIn.GetComponentType<TagComponent>()))
            {
                Value tagObject;
                tagObject.SetObject();

                TagComponent* pTag = sceneIn.Get<TagComponent>(entity);
                m_ParseTagToDoc(tagObject, *pTag, allocator);
                entityObject.AddMember("tag", tagObject, allocator);
            }
            if(pEntityManager->HasComponent(entity, sceneIn.GetComponentType<TransformComponent>()))
            {
                Value transformObject;
                transformObject.SetObject();

                TransformComponent* pTransform = sceneIn.Get<TransformComponent>(entity);
                m_ParseTransformToDoc(transformObject, *pTransform, allocator);
                entityObject.AddMember("transform", transformObject, allocator);
            }
            if (pEntityManager->HasComponent(entity, sceneIn.GetComponentType<MovementComponent>()))
            {
                Value movementObject;
                movementObject.SetObject();

                MovementComponent* pMovement = sceneIn.Get<MovementComponent>(entity);
                m_ParseMovementToDoc(movementObject, *pMovement, allocator);
                entityObject.AddMember("movement", movementObject, allocator);
            }
            if (pEntityManager->HasComponent(entity, sceneIn.GetComponentType<TextureComponent>()))
            {
                Value textureObject;
                textureObject.SetObject();

                TextureComponent* pTexture = sceneIn.Get<TextureComponent>(entity);
                m_ParseTextureToDoc(textureObject, *pTexture, allocator);
                entityObject.AddMember("texture", textureObject, allocator);
            }
            if (pEntityManager->HasComponent(entity, sceneIn.GetComponentType<MaterialComponent>()))
            {
                Value materialObject;
                materialObject.SetObject();

                MaterialComponent* pMaterial = sceneIn.Get<MaterialComponent>(entity);
                m_ParseMaterialToDoc(materialObject, *pMaterial, allocator);
                entityObject.AddMember("material", materialObject, allocator);
            }
            if (pEntityManager->HasComponent(entity, sceneIn.GetComponentType<LightComponent>()))
            {
                Value lightObject;
                lightObject.SetObject();

                LightComponent* pLight = sceneIn.Get<LightComponent>(entity);
                m_ParseLightToDoc(lightObject, *pLight, allocator);
                entityObject.AddMember("light", lightObject, allocator);
            }

            // Add the entityObject to the main JSON array
            m_doc.PushBack(entityObject, allocator);
        }

        return true;
    }

    bool SceneSerializerJSON::m_ParseTagToDoc(rapidjson::Value& jsonObject, 
                                              TagComponent& tagIn,
							                  rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "name", tagIn.name, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseTransformToDoc(rapidjson::Value& jsonObject, 
                                                    TransformComponent& transformIn,
							                        rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "position", transformIn.position, allocator);
        parser.SetMember(jsonObject, "orientation", transformIn.orientation, allocator);
        parser.SetMember(jsonObject, "scale", transformIn.scale, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseMovementToDoc(rapidjson::Value& jsonObject, 
                                                   MovementComponent& movementIn,
							                       rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "velocity", movementIn.velocity, allocator);
        parser.SetMember(jsonObject, "acceleration", movementIn.acceleration, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseTextureToDoc(rapidjson::Value& jsonObject, 
                                                  TextureComponent& textureIn, 
                                                  rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "fileName", textureIn.fileName, allocator);
        parser.SetMember(jsonObject, "textureType", textureIn.textureType, allocator);
        parser.SetMember(jsonObject, "vecTextures", textureIn.vecTextures, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseMaterialToDoc(rapidjson::Value& jsonObject, 
                                                   MaterialComponent& materialIn, 
                                                   rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.SetMember(jsonObject, "materialName", materialIn.materialName, allocator);
        parser.SetMember(jsonObject, "alphaTexture", materialIn.alphaTexture, allocator);
        parser.SetMember(jsonObject, "colorTextures", materialIn.colorTextures, allocator);
        parser.SetMember(jsonObject, "colorTexturesRatios", materialIn.colorTexturesRatios, allocator);
        parser.SetMember(jsonObject, "cubeTexture", materialIn.cubeTexture, allocator);
        parser.SetMember(jsonObject, "offset", materialIn.offset, allocator);
        parser.SetMember(jsonObject, "currOffset", materialIn.currOffset, allocator);
        parser.SetMember(jsonObject, "offsetHeightMap", materialIn.offsetHeightMap, allocator);
        parser.SetMember(jsonObject, "currOffsetHeightMap", materialIn.currOffsetHeightMap, allocator);
        parser.SetMember(jsonObject, "isEmissive", materialIn.offsetMove, allocator);
        parser.SetMember(jsonObject, "discardTexture", materialIn.discardTexture, allocator);
        parser.SetMember(jsonObject, "heightMapTexture", materialIn.heightMapTexture, allocator);
        parser.SetMember(jsonObject, "heightScale", materialIn.heightScale, allocator);
        parser.SetMember(jsonObject, "isEmissive", materialIn.isEmissive, allocator);
        parser.SetMember(jsonObject, "normalTexture", materialIn.normalTexture, allocator);
        parser.SetMember(jsonObject, "specularTexture", materialIn.specularTexture, allocator);
        parser.SetMember(jsonObject, "useAlphaTexture", materialIn.useAlphaTexture, allocator);
        parser.SetMember(jsonObject, "useCubeTexture", materialIn.useCubeTexture, allocator);
        parser.SetMember(jsonObject, "useDiscardTexture", materialIn.useDiscardTexture, allocator);
        parser.SetMember(jsonObject, "useHeightMap", materialIn.useHeightMap, allocator);
        parser.SetMember(jsonObject, "useNormalTexture", materialIn.useNormalTexture, allocator);
        parser.SetMember(jsonObject, "useSpecularTexture", materialIn.useSpecularTexture, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseLightToDoc(rapidjson::Value& jsonObject, LightComponent& lightIn, rapidjson::Document::AllocatorType& allocator)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();
        int textureType = 0;

        parser.SetMember(jsonObject, "distanceOffset", lightIn.distanceOffset, allocator);
        parser.SetMember(jsonObject, "atten", lightIn.atten, allocator);
        parser.SetMember(jsonObject, "diffuse", lightIn.diffuse, allocator);
        parser.SetMember(jsonObject, "direction", lightIn.direction, allocator);
        parser.SetMember(jsonObject, "directionOffset", lightIn.directionOffset, allocator);
        parser.SetMember(jsonObject, "params", lightIn.params, allocator);
        parser.SetMember(jsonObject, "position", lightIn.position, allocator);
        parser.SetMember(jsonObject, "specular", lightIn.specular, allocator);
        parser.SetMember(jsonObject, "status", lightIn.status, allocator);
        parser.SetMember(jsonObject, "ulBasePath", lightIn.ulBasePath, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseDocToScene(Scene& sceneOut)
    {
        using namespace rapidjson;

        bool isValid = m_doc.IsArray();
        if (!isValid)
        {
            LOG_ERROR("File not valid, expected array of entities!\n");
            return false;
        }

        // Go over each entity
        for (unsigned int entityIndex = 0; entityIndex < m_doc.Size(); entityIndex++)
        {
            Entity entityId = sceneOut.CreateEntity();

            Value& entityObject = m_doc[entityIndex];
            bool isValid = entityObject.IsObject();
            if (!isValid)
            {
                std::string error = "Entity #" + std::to_string(entityIndex) + 
                    " not valid, expected object of components!\n";
                LOG_ERROR(error);
                return false;
            }

            // Inside EntityID iterate over each component
            for (Value::ConstMemberIterator entityMember = entityObject.MemberBegin(); 
                 entityMember != entityObject.MemberEnd(); ++entityMember)
            {
                std::string componentName = entityMember->name.GetString();

                Value& componentObject = m_doc[entityIndex][entityMember->name];
                bool isValid = componentObject.IsObject();
                if (!isValid)
                {
                    std::string error = "Entity #" + std::to_string(entityIndex) + 
                        ", component '" + componentName + "' not valid\n";
                    LOG_ERROR(error);
                    return false;
                }

                if (componentName == "tag")
                {
                    TagComponent* pTag = sceneOut.AddComponent<TagComponent>(entityId);
                    m_ParseDocToTag(componentObject, *pTag);
                }
                else if (componentName == "transform")
                {
                    TransformComponent* pTransform = sceneOut.AddComponent<TransformComponent>(entityId);
                    m_ParseDocToTransform(componentObject, *pTransform);
                }
                else if (componentName == "movement")
                {
                    MovementComponent* pMovement = sceneOut.AddComponent<MovementComponent>(entityId);
                    m_ParseDocToMovement(componentObject, *pMovement);
                }
                else if (componentName == "texture")
                {
                    TextureComponent* pTexture = sceneOut.AddComponent<TextureComponent>(entityId);
                    m_ParseDocToTexture(componentObject, *pTexture);
                }
                else if (componentName == "material")
                {
                    MaterialComponent* pMaterial = sceneOut.AddComponent<MaterialComponent>(entityId);
                    m_ParseDocToMaterial(componentObject, *pMaterial);
                }
                else if (componentName == "light")
                {
                    LightComponent* pLight = sceneOut.AddComponent<LightComponent>(entityId);
                    m_ParseDocToLight(componentObject, *pLight);
                }
            }
        }

        return true;
    }

    bool SceneSerializerJSON::m_ParseDocToTag(rapidjson::Value& jsonObject, TagComponent& tagOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.GetValue(jsonObject["name"], tagOut.name);

        return true;
    }

    bool SceneSerializerJSON::m_ParseDocToTransform(rapidjson::Value& jsonObject, 
                                                    TransformComponent& transformOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.GetValue(jsonObject["position"], transformOut.position);
        parser.GetValue(jsonObject["orientation"], transformOut.orientation);
        parser.GetValue(jsonObject["scale"], transformOut.scale);

        return true;
    }

    bool SceneSerializerJSON::m_ParseDocToMovement(rapidjson::Value& jsonObject, 
                                                   MovementComponent& movementOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.GetValue(jsonObject["velocity"], movementOut.velocity);
        parser.GetValue(jsonObject["acceleration"], movementOut.acceleration);

        return true;
    }
    bool SceneSerializerJSON::m_ParseDocToTexture(rapidjson::Value& jsonObject, 
                                                  TextureComponent& textureOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();
        int textureType = 0;

        parser.GetValue(jsonObject["fileName"], textureOut.fileName);
        parser.GetValue(jsonObject["textureType"], textureType);
        parser.GetValue(jsonObject["vecTextures"], textureOut.vecTextures);

        textureOut.textureType = (eTextureType)textureType;

        return true;
    }
    bool SceneSerializerJSON::m_ParseDocToMaterial(rapidjson::Value& jsonObject, 
                                                   MaterialComponent& materialOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        parser.GetValue(jsonObject["materialName"], materialOut.materialName);
        parser.GetValue(jsonObject["alphaTexture"], materialOut.alphaTexture);
        parser.GetValue(jsonObject["colorTextures"], materialOut.colorTextures);
        parser.GetValue(jsonObject["colorTexturesRatios"], materialOut.colorTexturesRatios);
        parser.GetValue(jsonObject["cubeTexture"], materialOut.cubeTexture);
        parser.GetValue(jsonObject["offset"], materialOut.offset);
        parser.GetValue(jsonObject["currOffset"], materialOut.currOffset);
        parser.GetValue(jsonObject["offsetHeightMap"], materialOut.offsetHeightMap);
        parser.GetValue(jsonObject["currOffsetHeightMap"], materialOut.currOffsetHeightMap);
        parser.GetValue(jsonObject["isEmissive"], materialOut.offsetMove);
        parser.GetValue(jsonObject["discardTexture"], materialOut.discardTexture);
        parser.GetValue(jsonObject["heightMapTexture"], materialOut.heightMapTexture);
        parser.GetValue(jsonObject["heightScale"], materialOut.heightScale);
        parser.GetValue(jsonObject["isEmissive"], materialOut.isEmissive);
        parser.GetValue(jsonObject["normalTexture"], materialOut.normalTexture);
        parser.GetValue(jsonObject["specularTexture"], materialOut.specularTexture);
        parser.GetValue(jsonObject["useAlphaTexture"], materialOut.useAlphaTexture);
        parser.GetValue(jsonObject["useCubeTexture"], materialOut.useCubeTexture);
        parser.GetValue(jsonObject["useDiscardTexture"], materialOut.useDiscardTexture);
        parser.GetValue(jsonObject["useHeightMap"], materialOut.useHeightMap);
        parser.GetValue(jsonObject["useNormalTexture"], materialOut.useNormalTexture);
        parser.GetValue(jsonObject["useSpecularTexture"], materialOut.useSpecularTexture);

        return true;
    }
    bool SceneSerializerJSON::m_ParseDocToLight(rapidjson::Value& jsonObject, LightComponent& lightOut)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();
        int textureType = 0;

        parser.GetValue(jsonObject["distanceOffset"], lightOut.distanceOffset);
        parser.GetValue(jsonObject["atten"], lightOut.atten);
        parser.GetValue(jsonObject["diffuse"], lightOut.diffuse);
        parser.GetValue(jsonObject["direction"], lightOut.direction);
        parser.GetValue(jsonObject["directionOffset"], lightOut.directionOffset);
        parser.GetValue(jsonObject["params"], lightOut.params);
        parser.GetValue(jsonObject["position"], lightOut.position);
        parser.GetValue(jsonObject["specular"], lightOut.specular);
        parser.GetValue(jsonObject["status"], lightOut.status);
        parser.GetValue(jsonObject["ulBasePath"], lightOut.ulBasePath);

        return true;
    }
}
