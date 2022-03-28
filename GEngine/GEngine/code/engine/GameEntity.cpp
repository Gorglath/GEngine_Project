#include "GameEntity.h"

GameEntity::GameEntity()
{
	m_transform.m_gameEntity = this;
	//TODO Add Id.
}

void GameEntity::load()
{
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
