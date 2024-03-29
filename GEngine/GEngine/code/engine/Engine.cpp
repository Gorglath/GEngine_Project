#include "Engine.h"

Engine::~Engine()
{
    clean();
}

void Engine::init(GameState& gameState)
{
    m_graphicsSystem = GraphicSystem(&gameState);
    m_graphicsSystem.initialize("GEngine");

    bool isSoundEngineInitialized = m_soundSystem.intialize("C:\\Users\\User\\Desktop\\C++Projects\\GEngine\\GEngine\\GEngine\\assets\\sounds");
    if (!isSoundEngineInitialized)
        printf("Failed to load sound engine");

    m_soundSystem.play2DSound("roar.wav", true);
}

bool Engine::loadScene()
{

    if (m_graphicsSystem.getQuit())
    {
        m_graphicsSystem.deinitialize();
        return false;
    }

    m_graphicsSystem.createScene01();
    m_graphicsSystem.createScene02();

    m_time.init();
    
    return true;
}

bool Engine::update()
{
    m_graphicsSystem.beginFrameParallel();
    m_graphicsSystem.update(static_cast<float>(m_time.getDeltaTime()));
    m_graphicsSystem.finishFrameParallel();
    m_graphicsSystem.finishFrame();

    m_time.update();

    return m_graphicsSystem.getQuit();
}

void Engine::clean()
{
    m_graphicsSystem.destroyScene();
    m_graphicsSystem.deinitialize();
}
