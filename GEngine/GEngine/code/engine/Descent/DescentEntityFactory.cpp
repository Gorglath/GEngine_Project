#include "DescentEntityFactory.h"
namespace GEngine 
{
	namespace Descent 
	{
		SceneManager* GEngine::Descent::DescentEntityFactory::m_sceneManager{ nullptr };

		GameEntity GEngine::Descent::DescentEntityFactory::CreateEnemy(const std::string& name, const TransformDataStruct& transformData)
		{
			NormalEnemy enemyEntity;

			enemyEntity.m_name = name;

			enemyEntity.m_transform.m_position = transformData.m_location;
			enemyEntity.m_transform.m_eularAngles = transformData.m_eularAngles;
			enemyEntity.m_transform.m_scale = transformData.m_scale;

			enemyEntity.m_entityNode = enemyEntity.m_meshLoader.loadMesh("Enemy.mesh", "Models", m_sceneManager);
			return enemyEntity;
		}

		GameEntity GEngine::Descent::DescentEntityFactory::CreatePlayer(const std::string& name, const TransformDataStruct& transformData)
		{
			Player playerEntity;

			playerEntity.m_name = name;

			playerEntity.m_transform.m_position = transformData.m_location;
			playerEntity.m_transform.m_eularAngles = transformData.m_eularAngles;
			playerEntity.m_transform.m_scale = transformData.m_scale;

			return playerEntity;
		}

		GameEntity GEngine::Descent::DescentEntityFactory::CreatePickup(const std::string& name, const TransformDataStruct& transformData)
		{
			return GameEntity();
		}

		GameEntity GEngine::Descent::DescentEntityFactory::CreateStaticObject(const std::string& name, const TransformDataStruct& transformData)
		{
			return GameEntity();
		}
		void DescentEntityFactory::Init(SceneManager* sceneManagerPtr)
		{
			m_sceneManager = sceneManagerPtr;
		}
	}
}