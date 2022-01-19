#pragma once
#include "Ogre.h"
#include "OgreSceneManager.h"
#include "OgreItem.h"
#include "InputData.hpp"

using namespace Ogre;
	class SlidingSphere
	{
	public:
		SlidingSphere() = default;
		~SlidingSphere() = default;
		void createSphere(SceneManager* sceneManager);
		void update(float dt, InputData inputData);
		void setShouldApplyGravity(bool state) { m_shouldApplyGravity = state; }
		Item* getSphereMesh() const { return m_sphereMesh; }
	private:
		SceneNode* m_sphereNode = nullptr;
		Item* m_sphereMesh = nullptr;
		bool m_shouldApplyGravity = true;
	};

