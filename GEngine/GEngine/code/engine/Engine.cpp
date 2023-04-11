#include "Engine.h"
#include "Ogre.h"
#include <filesystem>
#include <iostream>
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

    //m_soundSystem.play2DSound("roar.wav", true);

    //Get the path to the current folder.
    std::filesystem::path app_path = std::filesystem::current_path();
    std::string app_path_string = app_path.string();

    Ogre::ResourceGroupManager* rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation(app_path_string + "\\assets\\models", "FileSystem","Models");
    rgm->addResourceLocation(app_path_string + "\\assets\\materials\\textures", "FileSystem","Textures");
    rgm->addResourceLocation(app_path_string + "\\assets\\materials\\scripts", "FileSystem","Scripts");
    
    rgm->initialiseAllResourceGroups(false);
    /*
    for (auto group : rgm->getResourceGroups())
    {
        std::cout << group << std::endl;
        for (auto location : rgm->getResourceLocationList(group))
        {
            std::cout << "     " << location->archive->getName() << std::endl;
        }
    }*/
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
