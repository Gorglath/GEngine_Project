#pragma once
#include "Component.h"
#include "OgreSceneManager.h"
#include "OgreItem.h"
#include "OgreMeshManager2.h"
#include "Ogre.h"
#include <string>
#include <iostream>
namespace GEngine
{
	class CompMeshLoader : public Component
	{
	public:
		CompMeshLoader() = default;
		~CompMeshLoader() = default;

		Ogre::SceneNode* loadMesh(const std::string& name,const std::string& group, Ogre::SceneManager* sceneManager)
		{
			m_mesh = sceneManager->createItem(name,group);

			m_sceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);

			m_sceneNode->attachObject(m_mesh);
			m_sceneNode->setPosition(0.0f, m_sceneNode->getScale().y / 2.0f, 0.0f);

			return m_sceneNode;
		}

		Ogre::SceneNode* loadPlane(Ogre::SceneManager* sceneManager)
		{
			Ogre::v1::MeshPtr planeMeshV1 = Ogre::v1::MeshManager::getSingleton().createPlane(
				"Plane v1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
				Ogre::Plane(Ogre::Vector3::UNIT_Y, 1.0f), 15.0f, 15.0f, 1, 1, true, 1, 4.0f, 4.0f,
				Ogre::Vector3::UNIT_Z, Ogre::v1::HardwareBuffer::HBU_STATIC,
				Ogre::v1::HardwareBuffer::HBU_STATIC);

			Ogre::MeshPtr planeMesh = Ogre::MeshManager::getSingleton().createByImportingV1(
				"Plane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeMeshV1.get(), true,
				true, true);

			m_mesh = sceneManager->createItem(planeMesh, Ogre::SCENE_DYNAMIC);
			m_mesh->setDatablock("Marble");
			m_sceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
				->createChildSceneNode(Ogre::SCENE_DYNAMIC);

			m_sceneNode->setPosition(0, -1, 0);
			m_sceneNode->attachObject(m_mesh);
		}

		Ogre::SceneNode* getSceneNode() const { return m_sceneNode; }
		Ogre::Item* getMesh() const { return m_mesh; }
		void update() override {}
		void destroy() override {}
	private:
		Ogre::SceneNode* m_sceneNode{ nullptr };
		Ogre::Item* m_mesh{ nullptr };
	};
}