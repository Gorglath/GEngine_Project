#include "Game.h"

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

void Game::createFloor()
{
	Ogre::v1::MeshPtr planeMeshV1 = Ogre::v1::MeshManager::getSingleton().createPlane(
		"Plane v1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 1.0f), 15.0f, 15.0f, 1, 1, true, 1, 4.0f, 4.0f,
		Ogre::Vector3::UNIT_Z, Ogre::v1::HardwareBuffer::HBU_STATIC,
		Ogre::v1::HardwareBuffer::HBU_STATIC);

	Ogre::MeshPtr planeMesh = Ogre::MeshManager::getSingleton().createByImportingV1(
		"Plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeMeshV1.get(), true,
		true, true);

	m_floor = m_sceneManager->createItem(planeMesh, Ogre::SCENE_DYNAMIC);
	m_floor->setDatablock("Marble");
	Ogre::SceneNode* sceneNode = m_sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
		->createChildSceneNode(Ogre::SCENE_DYNAMIC);

	sceneNode->setPosition(0, -1, 0);
	sceneNode->attachObject(m_floor);
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
