#include "CompCollider.h"
#include "GameEntity.h"
#include "CollisionUtils.h"
std::vector<CompCollider*> CompCollider::m_gColliders{};
CompCollider::CompCollider()
{
	m_gColliders.push_back(this);
}

void CompCollider::update()
{
	for (auto const& collider : m_gColliders)
	{
		if (this->m_gameEntity == collider->m_gameEntity)
			continue;
		else if (CollisionUtils::isColliding(this,collider))
			m_gameEntity->onColliderEnter(collider);
	}
}

void CompCollider::destroy()
{
	m_gColliders.erase(
		std::remove(m_gColliders.begin(), m_gColliders.end(), this),
		m_gColliders.end()
	);
}
