#include "JsonParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
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

            placeHolder = placeHolder.substr(placeHolder.find('~') + 1, placeHolder.size());

            entity = BuildGameEntityFromType(globalEntityData.m_name,globalEntityData.m_name,placeHolder,transformData);

            gameEntities.push_back(entity);
        }
        return gameEntities;
    }

    Descent::EDescentObjectType JsonToLevelParser::StringToDescentEnum(const std::string& objectType)
    {
        if (objectType == "OBSTACLE")
            return Descent::EDescentObjectType::PLAYER;
        
        if (objectType == "WALL")
            return Descent::EDescentObjectType::WALL;

        if (objectType == "FLOOR")
            return Descent::EDescentObjectType::FLOOR;

        if (objectType == "PICKUP")
            return Descent::EDescentObjectType::PICKABLE;

        if (objectType == "ENEMY")
            return Descent::EDescentObjectType::ENEMY;

        return Descent::EDescentObjectType::NONE;
    }

    GameEntity JsonToLevelParser::BuildGameEntityFromType(const std::string& objectName,
        const std::string& objectType, const std::string& objectData, const TransformDataStruct& transformData)
    {
        Descent::EDescentObjectType descentObjectType = StringToDescentEnum(objectType);
        GameEntity gameEntity;
        json objectDataJson = json::parse(objectData);

        if (descentObjectType == Descent::EDescentObjectType::ENEMY)
        {
            Descent::DescentEnemyDataStruct enemyData = objectDataJson;

            if (enemyData.m_enemyType == Descent::EDescentEnemyType::BOSS)
                gameEntity = Descent::DescentEntityFactory::CreateBossEnemy(objectName, transformData);
            else
                gameEntity = Descent::DescentEntityFactory::CreateNormalEnemy(objectName, transformData);

            return gameEntity;
        }

        if (descentObjectType == Descent::EDescentObjectType::PICKABLE)
        {
            Descent::DescentPickupDataStruct pickupData = objectDataJson;

            if (pickupData.m_pickupType == Descent::EDescentPickupType::AMMO)
                gameEntity = Descent::DescentEntityFactory::CreateAmmoPickup(objectName, transformData);
            else if (pickupData.m_pickupType == Descent::EDescentPickupType::HEALTH)
                gameEntity = Descent::DescentEntityFactory::CreateLifePickup(objectName, transformData);
            else if (pickupData.m_pickupType == Descent::EDescentPickupType::HOSTAGE)
                gameEntity = Descent::DescentEntityFactory::CreateHostagePickup(objectName, transformData);
            else
                gameEntity = Descent::DescentEntityFactory::CreateScorePickup(objectName, transformData);

            return gameEntity;
        }

        if (descentObjectType == Descent::EDescentObjectType::FLOOR)
        {
            Descent::DescentFloorDataStruct floorData = objectDataJson;

            std::string materialName;
            if (floorData.m_textureId == 0)
                materialName = "WallFloorRock";
            else if (floorData.m_textureId == 1)
                materialName = "MetalFloor";
            else if (floorData.m_textureId == 2)
                materialName = "FurFloor";

            if (floorData.m_floorType == Descent::EDescentFloorType::NORMAL)
                gameEntity = Descent::DescentEntityFactory::CreateNormalFloorObject(objectName, transformData,materialName);
            else
                gameEntity = Descent::DescentEntityFactory::CreateRampFloorObject(objectName, transformData,materialName);

            return gameEntity;
        }

        if (descentObjectType == Descent::EDescentObjectType::WALL)
        {
            Descent::DescentWallDataStruct wallData = objectDataJson;

            std::string materialName;
            if (wallData.m_textureId == 0)
                materialName = "MetalWall";
            else if (wallData.m_textureId == 1)
                materialName = "WallFloorRock";
            else if (wallData.m_textureId == 2)
                materialName = "FurWall";
           
            if (wallData.m_wallType == Descent::EDescentWallType::NORMAL)
                gameEntity = Descent::DescentEntityFactory::CreateNormalWallObject(objectName, transformData, materialName);
            else
                gameEntity = Descent::DescentEntityFactory::CreateRampWallObject(objectName, transformData, materialName);

            return gameEntity;
        }

        if (descentObjectType == Descent::EDescentObjectType::PLAYER)
        {
            gameEntity = Descent::DescentEntityFactory::CreatePlayer(objectName, transformData);

            return gameEntity;
        }
    }
}