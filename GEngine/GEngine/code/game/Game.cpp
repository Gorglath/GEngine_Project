#include "Game.h"
#include "../engine/CompMeshLoader.h"
#include "../engine/CompLight.h"
#include "../engine/Descent/DescentEntityFactory.h"
namespace GEngine
{
	void Game::init(GraphicSystem* graphicSystem)
	{
		m_sceneManager = graphicSystem->getSceneManager();
		Descent::DescentEntityFactory::Init(m_sceneManager);
	}

	void Game::createScene01()
	{
		GameState::createScene01();
	}

	void Game::update(float dt)
	{
	}

	void Game::destroyScene()
	{
		for (auto gameEntity : m_gameEntities)
		{
			gameEntity.destroy();
		}

		m_gameEntities.clear();
	}

	void Game::createFloor()
	{
		CompMeshLoader loader;
		loader.loadPlane(m_sceneManager);
		m_floor.addComponent(&loader);
	}

	void Game::createLight()
	{
		GameEntity lightEntity;

		CompLight lightComp;
		lightComp.initialize(m_sceneManager);

		lightEntity.addComponent(&lightComp);

	}
}