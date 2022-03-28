#pragma once
#include "Component.h"
#include "Ogre.h"
#include "OgreItem.h"
#include <string>

class CompMeshLoader : public Component
{
public:
	CompMeshLoader() = default;
	~CompMeshLoader() = default;

	Ogre::SceneNode* loadMesh(std::string name,Ogre::SceneManager* sceneManager)
	{
		m_mesh = sceneManager->createItem(name, Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,Ogre::SCENE_DYNAMIC);

		m_sceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);

		m_sceneNode->attachObject(m_mesh);
		m_sceneNode->setPosition(0.0f, m_sceneNode->getScale().y / 2.0f, 0.0f);

		return m_sceneNode;
	}

	Ogre::SceneNode* getSceneNode() const { return m_sceneNode; }
	Ogre::Item* getMesh() const { return m_mesh; }
	void update() override {}
	void destroy() override {}
private:
	Ogre::SceneNode* m_sceneNode{ nullptr };
	Ogre::Item* m_mesh{ nullptr };
};