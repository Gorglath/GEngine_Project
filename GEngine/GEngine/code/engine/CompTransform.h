#pragma once
#include "Component.h"
#include "Ogre.h"

using Ogre::Vector3;
class CompTransform :public Component
{
public:
	Vector3 m_position{ 0.0f,0.0f,0.0f };
	Vector3 m_scale{ 1.0f,1.0f,1.0f };
	Vector3 m_rotation{ 0.0f,0.0f,0.0f };

	void update(float dt) override {};
};