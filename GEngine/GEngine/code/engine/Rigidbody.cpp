#include "Rigidbody.h"

void Rigidbody::Initialize(SceneManager* sceneManager, RigidbodyShape shape, float mass, bool isDynamic, Vector3 initialPosition)
{
	m_bodyShape = shape;
	m_mass = mass;
	m_isDynamic = isDynamic;

	switch (shape)
	{
	case RigidbodyShape::SPHERE:
		m_bodyMesh = sceneManager->createItem(
			"Sphere1000.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
			Ogre::SCENE_DYNAMIC);

		m_bodyNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
			->createChildSceneNode(Ogre::SCENE_DYNAMIC);

		m_bodyNode->attachObject(m_bodyMesh);
		break;
	case RigidbodyShape::BOX:
		m_bodyMesh = sceneManager->createItem(
				"Cube_d.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
				Ogre::SCENE_DYNAMIC);

		m_bodyNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
			->createChildSceneNode(Ogre::SCENE_DYNAMIC);

		m_bodyNode->attachObject(m_bodyMesh);
		break;
	}
	m_linearVelocity = Vector3::ZERO;
	m_bodyNode->setPosition(initialPosition);
}

void Rigidbody::Update(float dt)
{
	Vector3 bodyPosition = m_bodyNode->getPosition();
	bodyPosition += m_linearVelocity * dt;
	m_bodyNode->setPosition(bodyPosition);
}

void Rigidbody::ApplyLinearVelocity(const Vector3 force)
{
	m_linearVelocity += force * m_mass;
}
