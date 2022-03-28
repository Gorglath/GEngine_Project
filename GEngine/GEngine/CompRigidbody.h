#pragma once
#include "code/engine/Component.h"
#include "OgreVector3.h"

using namespace Ogre;
class CompRigidbody : public Component
{
public:
	
	CompRigidbody() = default;
	~CompRigidbody() = default;
	
	void initialize(float mass, float friction, bool isStatic);

	void applyForce(Vector3 direction, float amount);
	
	void update() override {};
	void destroy() override;
private:
	Vector3 m_linearVelocity;
	Vector3 m_angularVelocity;
	float m_inverseMass;
	float m_friction;
	bool m_isStatic;
};