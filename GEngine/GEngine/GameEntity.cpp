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

void GameEntity::update()
{
	for (auto& component : m_components)
		if (component->m_isActive)
			component->update();

	onUpdate();
}

void GameEntity::onUpdate()
{
}

void GameEntity::destroy()
{
	for (auto& component : m_components)
		component->destroy();
}
