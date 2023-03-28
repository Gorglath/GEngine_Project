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

    GameEntity JsonToLevelParser::GetGameEntityFromType(const std::string& objectType, const std::string& objectData)
    {
        return GameEntity();
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

            entity = Descent::DescentEntityFactory::CreateNormalEnemy(globalEntityData.m_name + std::to_string(i), transformData);
           
            gameEntities.push_back(entity);
        }
        return gameEntities;
    }
}