#pragma once

#include "MessageQueueSystem.h"

class GameState;

class BaseSystem : public MessageQueueSystem
{
protected:
    GameState* m_currentGameState;

public:
    BaseSystem(GameState* gameState);
    BaseSystem() {}
    ~BaseSystem() override;

    virtual void initialize();
    virtual void deinitialize();

    virtual void createScene01();
    virtual void createScene02();

    virtual void destroyScene();

    void beginFrameParallel();
    void update(float timeSinceLast);
    void finishFrameParallel();
    void finishFrame();
};