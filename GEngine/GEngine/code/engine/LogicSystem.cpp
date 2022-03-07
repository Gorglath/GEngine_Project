#include "LogicSystem.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "SdlInputHandler.h"

#include "OgreConfigFile.h"
#include "OgreException.h"
#include "OgreRoot.h"

#include "OgreCamera.h"

#include "OgreArchiveManager.h"
#include "OgreHlmsManager.h"

#include "Compositor/OgreCompositorManager2.h"

#include "OgreOverlaySystem.h"

#include <SDL_syswm.h>

LogicSystem::LogicSystem(GameState* gameState) :
    BaseSystem(gameState),
    m_graphicsSystem(0),
    m_gameObjectManager(0),
    m_currentTransformIdx(1)
{
    for (Ogre::uint32 i = 2; i < 4 - 1; ++i)
        m_availableTransformIdx.push_back(i);
}
//-----------------------------------------------------------------------------------
LogicSystem::~LogicSystem() {}
//-----------------------------------------------------------------------------------
void LogicSystem::finishFrameParallel()
{
    if (m_gameObjectManager)
        m_gameObjectManager->finishFrameParallel();

    // Notify the GraphicsSystem we're done rendering this frame.
    if (m_graphicsSystem)
    {
        size_t idxToSend = m_currentTransformIdx;

        if (m_availableTransformIdx.empty())
        {
            // Don't relinquish our only ID left.
            // If you end up here too often, Graphics' thread is too slow,
            // or you need to increase NUM_GAME_ENTITY_BUFFERS
            idxToSend = std::numeric_limits<Ogre::uint32>::max();
        }
        else
        {
            // Until Graphics constantly releases the indices we send them, to avoid writing
            // to transform data that may be in use by the other thread (race condition)
            m_currentTransformIdx = m_availableTransformIdx.front();
            m_availableTransformIdx.pop_front();
        }

        this->queueSendMessage(m_graphicsSystem, LOGICFRAME_FINISHED, idxToSend);
    }

    BaseSystem::finishFrameParallel();
}
//-----------------------------------------------------------------------------------
void LogicSystem::processIncomingMessage(MessageId messageId, const void* data)
{
    switch (messageId)
    {
    case LOGICFRAME_FINISHED:
    {
        Ogre::uint32 newIdx = *reinterpret_cast<const Ogre::uint32*>(data);
        assert((m_availableTransformIdx.empty() ||
            newIdx == (m_availableTransformIdx.back() + 1) % NUM_GAME_ENTITY_BUFFERS) &&
            "Indices are arriving out of order!!!");

        m_availableTransformIdx.push_back(newIdx);
    }
    break;
    case GAME_ENTITY_SCHEDULED_FOR_REMOVAL_SLOT:
        m_gameObjectManager->_notifyGameEntitiesRemoved(
            *reinterpret_cast<const Ogre::uint32*>(data));
        break;
    case SDL_EVENT:
        // TODO
        break;
    default:
        break;
    }
}