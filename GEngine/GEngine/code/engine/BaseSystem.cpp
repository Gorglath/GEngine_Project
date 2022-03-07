#include "BaseSystem.h"
#include "GameState.h"

BaseSystem::BaseSystem(GameState* gameState) : m_currentGameState(gameState) {}
//-----------------------------------------------------------------------------------
BaseSystem::~BaseSystem() {}
//-----------------------------------------------------------------------------------
void BaseSystem::initialize() { m_currentGameState->initialize(); }
//-----------------------------------------------------------------------------------
void BaseSystem::deinitialize() { m_currentGameState->deinitialize(); }
//-----------------------------------------------------------------------------------
void BaseSystem::createScene01() { m_currentGameState->createScene01(); }
//-----------------------------------------------------------------------------------
void BaseSystem::createScene02() { m_currentGameState->createScene02(); }
//-----------------------------------------------------------------------------------
void BaseSystem::destroyScene() { m_currentGameState->destroyScene(); }
//-----------------------------------------------------------------------------------
void BaseSystem::beginFrameParallel() { this->processIncomingMessages(); }
//-----------------------------------------------------------------------------------
void BaseSystem::update(float timeSinceLast) { m_currentGameState->update(timeSinceLast); }
//-----------------------------------------------------------------------------------
void BaseSystem::finishFrameParallel()
{
    m_currentGameState->finishFrameParallel();

    this->flushQueuedMessages();
}
//-----------------------------------------------------------------------------------
void BaseSystem::finishFrame() { m_currentGameState->finishFrame(); }