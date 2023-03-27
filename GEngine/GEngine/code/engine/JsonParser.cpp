#include "JsonParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
namespace GEngine {

    struct GlobalEntityStruct
    {
    public:
        GlobalEntityStruct(const json& config)
        {
            config.at("m_objectType").get_to(m_name);
            config.at("m_id").get_to(m_id);
        };
        GlobalEntityStruct() {};
        std::string m_name{ };
        int m_id{ 0 };
    };

    
    struct TransformDataStruct {
    public:
        TransformDataStruct(const json& config) {
            m_location = config.at("m_location").get<GEngine::GVector3>();
            m_eularAngles = config.at("m_rotation").get<GEngine::GVector3>();
            m_scale = config.at("m_scale").get<GEngine::GVector3>();
        }

        TransformDataStruct() {

        }
        GVector3 m_location;
        GVector3 m_eularAngles;
        GVector3 m_scale;
    };
}

    std::vector<GameEntity> GEngine::JsonToLevelParser::GetGameEntitiesFromLevelJson(const std::string& levelName)
    {
        std::ifstream inFile;
        std::string path = "./assets/levels/" + levelName;
        inFile.open(path);

        std::stringstream strStream;
        strStream << inFile.rdbuf();

        std::string str = strStream.str();
        std::string segment;
        std::vector<std::string> splitObjects;
        while (std::getline(strStream, segment, '='))
        {
            splitObjects.push_back(segment);
        }

        std::string placeHolder;
        std::vector<GameEntity> gameEntities;
        GlobalEntityStruct globalEntityData;
        TransformDataStruct transformData;
        GameEntity entity;
        json globalDataJson;
        json vectorJson;
        for (int i = 0; i < splitObjects.size(); i++)
        {
            globalDataJson = json::parse(splitObjects[i].substr(0, splitObjects[i].find('~')));
            globalEntityData = globalDataJson;

            globalDataJson.clear();

            placeHolder = splitObjects[i].substr(splitObjects[i].find('~') + 1, splitObjects[i].size());
            
            vectorJson = json::parse(placeHolder.substr(0, placeHolder.find('~')));
            transformData = vectorJson;

            entity.m_name = globalEntityData.m_name + std::to_string(i);
            entity.m_id = globalEntityData.m_id;

            entity.m_transform.m_position = transformData.m_location;
            entity.m_transform.m_eularAngles = transformData.m_eularAngles;
            entity.m_transform.m_scale = transformData.m_scale;

            gameEntities.push_back(entity);
        }
        return gameEntities;
    }