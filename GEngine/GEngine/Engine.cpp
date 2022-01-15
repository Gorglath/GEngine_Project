#include "Engine.h"

Engine::~Engine()
{
    clean();
}

bool Engine::init()
{
    GameState gameState;
    m_graphicsSystem = GraphicSystem(&gameState);

    // MyGraphicsSystem::setupResources overrode the folder setup process to minimize errors.
    // But this also means you'll see "WARNING: LTC matrix textures could not be loaded.
    // Accurate specular IBL reflections and LTC area lights won't be available or may not
    // function properly!" message in the Log
    m_graphicsSystem.initialize("Tutorial 01: Initialization");

    if (m_graphicsSystem.getQuit())
    {
        m_graphicsSystem.deinitialize();
        return false;
    }

    m_graphicsSystem.createScene01();
    m_graphicsSystem.createScene02();

    m_time.init();
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
