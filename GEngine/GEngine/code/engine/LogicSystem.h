#pragma once

#include "BaseSystem.h"
#include "OgrePrerequisites.h"

#include <deque>

class GameObjectManager;

class LogicSystem : public BaseSystem
{
protected:
    BaseSystem* m_graphicsSystem;
    GameObjectManager* m_gameObjectManager;

    Ogre::uint32 m_currentTransformIdx;
    std::deque<Ogre::uint32> m_availableTransformIdx;

    /// @see MessageQueueSystem::processIncomingMessage
    void processIncomingMessage(MessageId messageId, const void* data) override;

public:
    LogicSystem(GameState* gameState);
    ~LogicSystem() override;

    void _notifyGraphicsSystem(BaseSystem* graphicsSystem) { m_graphicsSystem = graphicsSystem; }
    void _notifyGameEntityManager(GameObjectManager* mgr) { m_gameObjectManager = mgr; }

    void finishFrameParallel();

    GameObjectManager* getGameEntityManager() { return m_gameObjectManager; }
    Ogre::uint32 getCurrentTransformIdx() const { return m_currentTransformIdx; }
};