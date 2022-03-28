#include "Game.h"
#include "../engine/CompMeshLoader.h"
void Game::init(GraphicSystem* graphicSystem)
{
	m_sceneManager = graphicSystem->getSceneManager();
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
	Light* light = m_sceneManager->createLight();
	SceneNode* node = m_sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
	node->attachObject(light);
	light->setPowerScale(1.0f);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());

	m_sceneManager->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f,
		Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f,
		-light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);
}
