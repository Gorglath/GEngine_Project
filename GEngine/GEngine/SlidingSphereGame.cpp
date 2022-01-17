#include "SlidingSphereGame.h"

void SlidingSphereGame::createScene01()
{
	createFloor();
	createLight();

	m_sphere.createSphere(m_sceneManager);

	GameState::createScene01();
}

void SlidingSphereGame::update(float dt)
{
	m_sphere.update(dt);
	Vector3 pos = m_sphere.getSphereMesh()->getParentNode()->getPosition();
	Vector3 scale = m_sphere.getSphereMesh()->getParentNode()->getScale();
	if (pos.y - scale.y/2.0f <= 0.0f)
	{
		m_sphere.setShouldApplyGravity(false);
	}
}
