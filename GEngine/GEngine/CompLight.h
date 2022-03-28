#pragma once
#include "code/engine/Component.h"
#include "OgreSceneManager.h"
class CompLight : public Component 
{
public:
	CompLight() = default;
	~CompLight() = default;

	void initialize(Ogre::SceneManager* sceneManager)
	{
		m_light = sceneManager->createLight();
		m_sceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
		m_sceneNode->attachObject(m_light);

		m_light->setPowerScale(1.0f);
		m_light->setType(Ogre::Light::LT_DIRECTIONAL);
		m_light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());
	}

	void setPower(float power) { m_light->setPowerScale(power); }
	void setType(Ogre::Light::LightTypes type) { m_light->setType(type); }
	void setDirection(Ogre::Vector3 direction) { m_light->setDirection(direction); }
	void update() override {};
	void destroy() override {};
private:
	Ogre::SceneNode* m_sceneNode{ nullptr };
	Ogre::Light* m_light{ nullptr };
};