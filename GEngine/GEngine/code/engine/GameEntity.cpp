#include "GameEntity.h"

namespace GEngine {
	GameEntity::GameEntity()
	{
		m_transform.m_gameEntity = this;
		//TODO Add Id.
	}

	void GameEntity::load()
	{
		if (!m_entityNode)
			return;

		m_entityNode->scale(m_transform.m_scale);
		m_entityNode->setOrientation(m_transform.m_rotation);
		m_entityNode->setPosition(m_transform.m_position);
	}

	void GameEntity::start()
	{
		onStart();
		m_isInitialized = true;
	}

	void GameEntity::onStart()
	{
	}

	void GameEntity::update(float dt)
	{
		for (auto& component : m_components)
			if (component->m_isActive)
				component->update();

		onUpdate(dt);
	}

	void GameEntity::onUpdate(float dt)
	{
	}

	void GameEntity::onColliderEnter(CompCollider* collider)
	{
	}

	void GameEntity::destroy()
	{
		for (auto& component : m_components)
			component->destroy();
	}
}