#include "GameObjectManager.h"
#include "GameObject.h"

#include "LogicSystem.h"
const size_t cNumTransforms = 250;


GameObjectManager::GameObjectManager(MessageQueueSystem* graphicsSystem, LogicSystem* logicSystem) :
	m_currentId{ 0 },
	m_scheduledForRemovalCurrentSlot{ std::numeric_limits<size_t>::max() },
	m_graphicsSystem{ graphicsSystem },
	m_logicSystem{ logicSystem }
{
	m_logicSystem->
}

GameObjectManager::~GameObjectManager()
{
}

size_t GameObjectManager::getScheduledForRemovalAvailableSlot()
{
	return size_t();
}

void GameObjectManager::destroyAllGameEntitiesIn(GameObjectsVec& container)
{
}

void GameObjectManager::aquireTransformSlot(size_t& outSlot, size_t& outBufferIdx)
{
}

void GameObjectManager::releaseTransformSlot(size_t bufferIdx, GameObjectTransform* transform)
{
}

GameObject* GameObjectManager::addGameEntity(Ogre::SceneMemoryMgrTypes type, const MovableObjectDefinition* moDefinition, const Ogre::Vector3& initialPos, const Ogre::Quaternion& initialRot, const Ogre::Vector3& initialScale)
{
	return nullptr;
}

void GameObjectManager::removeGameEntity(GameObject* toRemove)
{
}

void GameObjectManager::_notifyGameEntitiesRemoved(size_t slot)
{
}

void GameObjectManager::finishFrameParallel()
{
}
