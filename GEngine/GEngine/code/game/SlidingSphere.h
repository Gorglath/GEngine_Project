#pragma once
//#include "Ogre.h"
#include "../engine/InputData.hpp"
#include "../engine/GameEntity.h"

using namespace Ogre;
	class SlidingSphere : public GameEntity
	{
	public:
		SlidingSphere() = default;
		~SlidingSphere() = default;
		void createSphere(SceneManager* sceneManager);
		void update(float dt, InputData inputData);
	private:
		void clampNewPositionToBounds(GEngine::GVector3& newPos);
		void clampAcceleration(GEngine::GVector3& desiredVelocity, float dt);
		GEngine::GVector3 m_velocity = GEngine::GVector3::zeroVector;
		FloatRect m_allowedArea = FloatRect(-6.8f, 6.8f, 6.8f, -6.8f);
		float m_accelerationSpeed = 10.0f;
		float m_movementSpeed = 10.0f;
		float m_bounceiness = 0.5f;
	};

