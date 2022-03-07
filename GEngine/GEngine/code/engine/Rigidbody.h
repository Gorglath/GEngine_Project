#pragma once
#include "Ogre.h"
#include "OgreItem.h"
#include "OgreSceneManager.h"

enum class RigidbodyShape
{
	NONE,
	SPHERE,
	BOX
};
using namespace Ogre;
class Rigidbody
{
public:
	Rigidbody() = default;
	~Rigidbody() = default;

	void Initialize(SceneManager* sceneManager, RigidbodyShape shape,float mass, bool isDynamic,Vector3 initialPosition);
	void Update(float dt);
	void ApplyLinearVelocity(const Vector3 force);
private:
	RigidbodyShape m_bodyShape{ RigidbodyShape::NONE };
	SceneNode* m_bodyNode{ nullptr };
	Item* m_bodyMesh{ nullptr };
	float m_mass{ 1.0f };
	bool m_isDynamic{ false };
	Vector3 m_linearVelocity{ Vector3::ZERO };

};