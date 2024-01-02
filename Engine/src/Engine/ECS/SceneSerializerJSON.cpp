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
        this->m_doc.SetObject();
    }

    SceneSerializerJSON::~SceneSerializerJSON()
    {
    }

    bool SceneSerializerJSON::DeserializeScene(const std::string& filePath, Scene& sceneOut)
    {
        bool isLoaded = this->m_LoadDoc(filePath);
        if (!isLoaded)
        {
            return false;
        }

        // Parse config and load into structure
        bool isParsed = this->m_ParseDocToScene(sceneOut);
        if (!isParsed)
        {
            std::string errorMsg = "Error parsing file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        this->m_doc.RemoveAllMembers();

        return true;
    }

    bool SceneSerializerJSON::SerializeScene(const std::string& filePath, Scene& sceneIn)
    {
        // Call the function to convert the doc to a JSON document
        bool isParsed = this->m_ParseSceneToDoc(sceneIn);
        if (!isParsed)
        {
            std::string errorMsg = "Error parsing doc to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        bool isSaved = this->m_SaveDoc(filePath);

        if (!isSaved) {
            std::string errorMsg = "Error saving json to file '" + filePath + "'";
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        this->m_doc.RemoveAllMembers();

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
            LOG_ERROR(errorMsg.c_str());
            return false;
        }

        char readBuffer[MAX_LINE_LENGTH];
        FileReadStream fs(fp, readBuffer, sizeof(readBuffer));

        this->m_doc.ParseStream(fs);

        fclose(fp);

        return true;
    }

    bool SceneSerializerJSON::m_SaveDoc(const std::string& filePath)
    {
        using namespace rapidjson;

        StringBuffer buf;
        PrettyWriter<StringBuffer> writer(buf);

        this->m_doc.Accept(writer);

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
        return true;
    }

    bool SceneSerializerJSON::m_ParseTagToDoc(rapidjson::Value& jsonObject, 
                                              TagComponent& tagIn)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        Document::AllocatorType& allocator = this->m_doc.GetAllocator();

        parser.SetMember(jsonObject, "name", tagIn.name, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseTransformToDoc(rapidjson::Value& jsonObject, 
                                                    TransformComponent& transformIn)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        Document::AllocatorType& allocator = this->m_doc.GetAllocator();

        parser.SetMember(jsonObject, "position", transformIn.position, allocator);
        parser.SetMember(jsonObject, "orientation", transformIn.orientation, allocator);
        parser.SetMember(jsonObject, "scale", transformIn.scale, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseMovementToDoc(rapidjson::Value& jsonObject, 
                                                   MovementComponent& movementIn)
    {
        using namespace rapidjson;

        ParserJSON parser = ParserJSON();

        Document::AllocatorType& allocator = this->m_doc.GetAllocator();

        parser.SetMember(jsonObject, "velocity", movementIn.velocity, allocator);
        parser.SetMember(jsonObject, "acceleration", movementIn.acceleration, allocator);

        return true;
    }

    bool SceneSerializerJSON::m_ParseDocToScene(Scene& sceneOut)
    {
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

        parser.GetValue(this->m_doc["velocity"], movementOut.velocity);
        parser.GetValue(this->m_doc["acceleration"], movementOut.acceleration);

        return true;
    }
}
