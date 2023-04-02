#include "DescentEntityFactory.h"
namespace GEngine 
{
	namespace Descent 
	{
		SceneManager* GEngine::Descent::DescentEntityFactory::m_sceneManager{ nullptr };

		GameEntity GEngine::Descent::DescentEntityFactory::CreateNormalEnemy(const std::string& name, const TransformDataStruct& transformData)
		{
			NormalEnemy enemyEntity;

			enemyEntity.m_name = name;

			enemyEntity.m_transform.m_position = transformData.m_location;
			enemyEntity.m_transform.m_eularAngles = transformData.m_eularAngles;
			enemyEntity.m_transform.m_scale = transformData.m_scale;
			enemyEntity.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			enemyEntity.m_entityNode = enemyEntity.m_meshLoader.loadMesh("Enemy.mesh", "Models", m_sceneManager);
			enemyEntity.load();
			return enemyEntity;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreateBossEnemy(const std::string& name, const TransformDataStruct& transformData)
		{
			NormalEnemy enemyEntity;

			enemyEntity.m_name = name;

			enemyEntity.m_transform.m_position = transformData.m_location;
			enemyEntity.m_transform.m_eularAngles = transformData.m_eularAngles;
			enemyEntity.m_transform.m_scale = transformData.m_scale;
			enemyEntity.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			enemyEntity.m_entityNode = enemyEntity.m_meshLoader.loadMesh("Enemy.mesh", "Models", m_sceneManager);//TODO: add different mesh for boss.
			enemyEntity.load();
			return enemyEntity;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreatePlayer(const std::string& name, const TransformDataStruct& transformData)
		{
			Player playerEntity;

			playerEntity.m_name = name;

			playerEntity.m_transform.m_position = transformData.m_location;
			playerEntity.m_transform.m_eularAngles = transformData.m_eularAngles;
			playerEntity.m_transform.m_scale = transformData.m_scale;
			playerEntity.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			playerEntity.load();
			return playerEntity;
		}

		GameEntity GEngine::Descent::DescentEntityFactory::CreateHostagePickup(const std::string& name, const TransformDataStruct& transformData)
		{
			HostagePickable hostagePickable;

			hostagePickable.m_name = name;

			hostagePickable.m_transform.m_position = transformData.m_location;
			hostagePickable.m_transform.m_eularAngles = transformData.m_eularAngles;
			hostagePickable.m_transform.m_scale = transformData.m_scale;
			hostagePickable.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			hostagePickable.m_entityNode = hostagePickable.m_meshLoader.loadMesh("Hostage.mesh", "Models", m_sceneManager);
			hostagePickable.load();
			return hostagePickable;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreateScorePickup(const std::string& name, const TransformDataStruct& transformData)
		{
			ScorePickable scorePickable;

			scorePickable.m_name = name;

			scorePickable.m_transform.m_position = transformData.m_location;
			scorePickable.m_transform.m_eularAngles = transformData.m_eularAngles;
			scorePickable.m_transform.m_scale = transformData.m_scale;
			scorePickable.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			scorePickable.m_entityNode = scorePickable.m_meshLoader.loadMesh("Score.mesh", "Models", m_sceneManager);
			
			scorePickable.load();
			return scorePickable;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreateLifePickup(const std::string& name, const TransformDataStruct& transformData)
		{
			LifePickable lifePickable;

			lifePickable.m_name = name;

			lifePickable.m_transform.m_position = transformData.m_location;
			lifePickable.m_transform.m_eularAngles = transformData.m_eularAngles;
			lifePickable.m_transform.m_scale = transformData.m_scale;
			lifePickable.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			lifePickable.m_entityNode = lifePickable.m_meshLoader.loadMesh("Life.mesh", "Models", m_sceneManager);
			lifePickable.load();
			return lifePickable;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreateAmmoPickup(const std::string& name, const TransformDataStruct& transformData)
		{
			AmmoPickable ammoPickable;

			ammoPickable.m_transform.m_position = transformData.m_location;
			ammoPickable.m_transform.m_eularAngles = transformData.m_eularAngles;
			ammoPickable.m_transform.m_scale = transformData.m_scale;
			ammoPickable.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			ammoPickable.m_entityNode = ammoPickable.m_meshLoader.loadMesh("Ammo.mesh", "Models", m_sceneManager);
			ammoPickable.load();
			return ammoPickable;
		}	

		GameEntity GEngine::Descent::DescentEntityFactory::CreateRampFloorObject(const std::string& name, const TransformDataStruct& transformData)
		{
			StaticObject staticObject;

			staticObject.m_name = name;

			staticObject.m_transform.m_position = transformData.m_location;
			staticObject.m_transform.m_eularAngles = transformData.m_eularAngles;
			staticObject.m_transform.m_scale = transformData.m_scale;
			staticObject.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			staticObject.m_entityNode = staticObject.m_meshLoader.loadMesh("RampFloor.mesh", "Models", m_sceneManager);
			staticObject.load();
			return staticObject;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreateRampWallObject(const std::string& name, const TransformDataStruct& transformData)
		{
			StaticObject staticObject;

			staticObject.m_name = name;

			staticObject.m_transform.m_position = transformData.m_location;
			staticObject.m_transform.m_eularAngles = transformData.m_eularAngles;
			staticObject.m_transform.m_scale = transformData.m_scale;
			staticObject.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			staticObject.m_entityNode = staticObject.m_meshLoader.loadMesh("RampWall.mesh", "Models", m_sceneManager);
			staticObject.load();
			return staticObject;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreateNormalFloorObject(const std::string& name, const TransformDataStruct& transformData) 
		{
			StaticObject staticObject;

			staticObject.m_name = name;

			staticObject.m_transform.m_position = transformData.m_location;
			staticObject.m_transform.m_eularAngles = transformData.m_eularAngles;
			staticObject.m_transform.m_scale = transformData.m_scale;
			staticObject.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			staticObject.m_entityNode = staticObject.m_meshLoader.loadMesh("NormalFloor.mesh", "Models", m_sceneManager);
			staticObject.load();
			return staticObject;
		}
		GameEntity GEngine::Descent::DescentEntityFactory::CreateNormalWallObject(const std::string& name, const TransformDataStruct& transformData)
		{
			StaticObject staticObject;

			staticObject.m_name = name;

			staticObject.m_transform.m_position = transformData.m_location;
			staticObject.m_transform.m_eularAngles = transformData.m_eularAngles;
			staticObject.m_transform.m_scale = transformData.m_scale;
			staticObject.m_transform.m_rotation = GQuaternion::Eular(transformData.m_eularAngles);

			staticObject.m_entityNode = staticObject.m_meshLoader.loadMesh("NormalWall.mesh", "Models", m_sceneManager);
			staticObject.load();
			return staticObject;
		}
		void DescentEntityFactory::Init(SceneManager* sceneManagerPtr)
		{
			m_sceneManager = sceneManagerPtr;
		}
	}
}