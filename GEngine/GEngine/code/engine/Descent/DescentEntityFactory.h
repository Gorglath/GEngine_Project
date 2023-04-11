#pragma once
#include "../GameEntity.h"
#include "../../game/Descent/NormalEnemy.h"
#include "../../game/Descent/BossEnemy.h"
#include "../../game/Descent/Player.h"
#include "../../game/Descent/AmmoPickable.h"
#include "../../game/Descent/LifePickable.h"
#include "../../game/Descent/ScorePickable.h"
#include "../../game/Descent/HostagePickable.h"
#include "../../game/Descent/StaticObject.h"

namespace GEngine 
{
	namespace Descent 
	{
		class DescentEntityFactory 
		{
			DescentEntityFactory() = delete;
			~DescentEntityFactory() = delete;
			DescentEntityFactory(const DescentEntityFactory&) = delete;

			static SceneManager* m_sceneManager;
		public:
			static void Init(SceneManager* sceneManagerPtr);
			static GameEntity CreateNormalEnemy(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreateBossEnemy(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreatePlayer(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreateHostagePickup(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreateScorePickup(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreateLifePickup(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreateAmmoPickup(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreateRampFloorObject(const std::string& name, const TransformDataStruct& transformData, const std::string& materialName);
			static GameEntity CreateRampWallObject(const std::string& name, const TransformDataStruct& transformData, const std::string& materialName);
			static GameEntity CreateNormalFloorObject(const std::string& name, const TransformDataStruct& transformData, const std::string& materialName);
			static GameEntity CreateNormalWallObject(const std::string& name, const TransformDataStruct& transformData, const std::string& materialName);
		};
	}
}