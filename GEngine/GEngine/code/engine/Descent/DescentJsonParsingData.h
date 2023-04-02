#pragma once
#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
namespace GEngine 
{
    namespace Descent 
    {
        enum class EDescentObjectType
        {
            NONE,
            PLAYER,
            WALL,
            FLOOR,
            ENEMY,
            PICKABLE
        };

        enum class EDescentEnemyType
        {
            NONE,
            NORMAL,
            FAST,
            BURST,
            BOSS
        };
        
        enum class EDescentWallType
        {
            NONE,
            NORMAL,
            RAMP
        };

        enum class EDescentFloorType
        {
            NONE,
            NORMAL,
            RAMP
        };

        enum class EDescentPickupType
        {
            NONE,
            SCORE,
            HEALTH,
            AMMO,
            HOSTAGE
        };

        struct DescentEnemyDataStruct
        {
        public:
            DescentEnemyDataStruct(const json& config) 
            {
                std::string placeHolder;
                config.at("m_enemyType").get_to(placeHolder);
                if (placeHolder == "NORMAL")
                    m_enemyType = EDescentEnemyType::NORMAL;
                else if (placeHolder == "BOSS")
                    m_enemyType = EDescentEnemyType::BOSS;
                else
                    m_enemyType = EDescentEnemyType::NONE;

                config.at("m_enemyHealth").get_to(m_enemyHealth);
                config.at("m_enemyTypeIndex").get_to(m_enemyTypeIndex);
                
            };
            EDescentEnemyType m_enemyType;
            int m_enemyHealth;
            int m_enemyTypeIndex;
        };

        struct DescentPickupDataStruct
        {
        public: 
            DescentPickupDataStruct(const json& config)
            {
                std::string placeHolder;
                config.at("m_pickupType").get_to(placeHolder);

                if (placeHolder == "SCORE")
                    m_pickupType = EDescentPickupType::SCORE;
                else if (placeHolder == "HEALTH")
                    m_pickupType = EDescentPickupType::HEALTH;
                else if (placeHolder == "HOSTAGE")
                    m_pickupType = EDescentPickupType::HOSTAGE;
                else if (placeHolder == "AMMO")
                    m_pickupType = EDescentPickupType::AMMO;
                else
                    m_pickupType = EDescentPickupType::NONE;

                config.at("m_pickupIndex").get_to(m_pickupIndex);
                config.at("m_scoreAmount").get_to(m_scoreAmount);
                config.at("m_lifeCount").get_to(m_lifeCount);
                config.at("m_ammoAmount").get_to(m_ammoAmount);
            };
            EDescentPickupType m_pickupType;
            int m_pickupIndex;
            int m_scoreAmount;
            int m_lifeCount;
            int m_ammoAmount;
        };

        
        struct DescentWallDataStruct
        {
        public:
            DescentWallDataStruct(const json& config)
            {
                std::string placeHolder;
                config.at("m_wallType").get_to(placeHolder);
                
                if (placeHolder == "NORMAL")
                    m_wallType = EDescentWallType::NORMAL;
                else if (placeHolder == "RAMP")
                    m_wallType = EDescentWallType::RAMP;
                else
                    m_wallType = EDescentWallType::NONE;

                config.at("m_textureId").get_to(m_textureId);
            };
            EDescentWallType m_wallType;
            int m_textureId;
        };

        struct DescentFloorDataStruct
        {
        public:
            DescentFloorDataStruct(const json& config)
            {
                std::string placeHolder;
                config.at("m_floorType").get_to(placeHolder);

                if (placeHolder == "NORMAL")
                    m_floorType = EDescentFloorType::NORMAL;
                else if (placeHolder == "RAMP")
                    m_floorType = EDescentFloorType::RAMP;
                else
                    m_floorType = EDescentFloorType::NONE;

                config.at("m_textureId").get_to(m_textureId);
            };
            EDescentFloorType m_floorType;
            int m_textureId;
        };
    }
}