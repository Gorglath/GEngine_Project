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
			static GameEntity CreateEnemy(const std::string& name,const TransformDataStruct& transformData); //TODO add different enemies type.
			static GameEntity CreatePlayer(const std::string& name, const TransformDataStruct& transformData);
			static GameEntity CreatePickup(const std::string& name, const TransformDataStruct& transformData); //TODO add different type of pickups creation.
			static GameEntity CreateStaticObject(const std::string& name, const TransformDataStruct & transformData);
		};
	}
}