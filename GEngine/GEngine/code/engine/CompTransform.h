#pragma once
#include "Component.h"
#include "OgreVector3.h"
#include "OgreQuaternion.h"
class CompTransform : public Component
{
public:
	Ogre::Vector3 m_position{ 0.0f,0.0f,0.0f };
	Ogre::Vector3 m_scale{ 1.0f,1.0f,1.0f };
	Ogre::Vector3 m_eularAngles{ 0.0f,0.0f,0.0f };
	Ogre::Quaternion m_rotation{ 0.0f,0.0f,0.0f,1.0f };

	void update() override {};
	void destroy() override {};
};