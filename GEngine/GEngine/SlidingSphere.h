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
		Item* getSphereMesh() const { return m_sphereMesh; }
	private:
		void clampNewPositionToBounds(Vector3& newPos);
		void clampAcceleration(Vector3 desiredVelocity, float dt);
		SceneNode* m_sphereNode = nullptr;
		Item* m_sphereMesh = nullptr;
		Vector3 m_velocity = Vector3::ZERO;
		FloatRect m_allowedArea = FloatRect(-6.8f, 6.8f, 6.8f, -6.8f);
		float m_accelerationSpeed = 10.0f;
		float m_movementSpeed = 10.0f;
		float m_bounceiness = 0.5f;
	};

