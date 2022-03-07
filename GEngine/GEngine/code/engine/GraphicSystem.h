#pragma once

#include "OgreOverlayPrerequisites.h"
#include "OgrePrerequisites.h"

#include "BaseSystem.h"

#include "GameObjectManager.h"
#include "OgreColourValue.h"
#include "OgreOverlaySystem.h"
#include "SdlEmulationLayer.h"
#include "StaticPluginLoader.h"
#include "Threading/OgreUniformScalableTask.h"

#include <SDL2/SDL.h>
using namespace Ogre;

class SdlInputHandler;

class GraphicSystem : public BaseSystem, public Ogre::UniformScalableTask
{
private:
    using BaseSystem::initialize;
protected:

    void handleWindowEvent(const SDL_Event& evt);

    static void addResourceLocation(const Ogre::String& archName, const Ogre::String& typeName,
        const Ogre::String& secName);

    bool isWriteAccessFolder(const Ogre::String& folderPath, const Ogre::String& fileToSave);

    /// @see MessageQueueSystem::processIncomingMessage
    void processIncomingMessage(MessageId messageId, const void* data) override;

    void loadTextureCache();
    void saveTextureCache();
    void loadHlmsDiskCache();
    void saveHlmsDiskCache();

    virtual void setupResources();
    virtual void registerHlms();
    /// Optional override method where you can perform resource group loading
    /// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    virtual void loadResources();
    virtual void chooseSceneManager();
    virtual void createCamera();
    /// Virtual so that advanced samples such as Sample_Compositor can override this
    /// method to change the default behavior if setupCompositor() is overridden, be
    /// aware @mBackgroundColour will be ignored
    virtual Ogre::CompositorWorkspace* setupCompositor();

    /// Called right before initializing Ogre's first window, so the params can be customized
    virtual void initMiscParamsListener(Ogre::NameValuePairList& params);

    /// Optional override method where you can create resource listeners (e.g. for loading screens)
    virtual void createResourceListener() {}

    void gameObjectAdded(const GameObjectManager::CreatedGameObject* createdGameEntity);
    void gameObjectRemove(GameObject* toRemove);

public:
    GraphicSystem(GameState* gameState, Ogre::String resourcePath = Ogre::String(""),
        Ogre::ColourValue backgroundColour = Ogre::ColourValue(0.2f, 0.4f, 0.6f));
    GraphicSystem() {}
    ~GraphicSystem() override;

    void _notifyLogicSystem(BaseSystem* logicSystem) { m_logicSystem = logicSystem; }

    void initialize(const Ogre::String& windowTitle);
    void deinitialize() override;

    void update(float timeSinceLast);

    void updateGameObjects(const GameObjectsVec& gameEntities, float weight);

    /// Overload Ogre::UniformScalableTask. @see updateGameEntities
    void execute(size_t threadId, size_t numThreads) override;

    /// Returns the GameEntities that are ready to be rendered. May include entities
    /// that are scheduled to be removed (i.e. they are no longer updated by logic)
    const GameObjectsVec& getGameEntities(Ogre::SceneMemoryMgrTypes type) const
    {
        return m_gameObjects[type];
    }

    SdlInputHandler* getInputHandler() { return m_inputHandler; }

    void setQuit() { m_quit = true; }
    bool getQuit() const { return m_quit; }

    float getAccumTimeSinceLastLogicFrame() const { return m_accumTimeSinceLastLogicFrame; }

    Ogre::Root* getRoot() const { return m_root; }
    Ogre::Window* getRenderWindow() const { return m_renderWindow; }
    Ogre::SceneManager* getSceneManager() const { return m_sceneManager; }
    Ogre::Camera* getCamera() const { return m_camera; }
    Ogre::CompositorWorkspace* getCompositorWorkspace() const { return m_workspace; }
    Ogre::v1::OverlaySystem* getOverlaySystem() const { return m_overlaySystem; }

    void setAlwaysAskForConfig(bool alwaysAskForConfig) {m_alwaysAskForConfig = alwaysAskForConfig;}
    bool getAlwaysAskForConfig() const { return m_alwaysAskForConfig; }

    const Ogre::String& getPluginsFolder() const { return m_pluginsFolder; }
    const Ogre::String& getWriteAccessFolder() const { return m_writeAccessFolder; }
    const Ogre::String& getResourcePath() const { return m_resourcePath; }
    const char* getMediaReadArchiveType() const;

    virtual void stopCompositor();
    virtual void restartCompositor();

    BaseSystem* m_logicSystem;

    SDL_Window* m_sdlWindow;
    SdlInputHandler* m_inputHandler;

    Ogre::Root* m_root;
    Ogre::Window* m_renderWindow;
    Ogre::SceneManager* m_sceneManager;
    Ogre::Camera* m_camera;
    Ogre::CompositorWorkspace* m_workspace;
    Ogre::String m_pluginsFolder;
    Ogre::String m_writeAccessFolder;
    Ogre::String m_resourcePath;

    Ogre::v1::OverlaySystem* m_overlaySystem;

    StaticPluginLoader m_staticPluginLoader;

    float m_accumTimeSinceLastLogicFrame;
    Ogre::uint32 m_currentTransformIdx;
    GameObjectsVec m_gameObjects[Ogre::NUM_SCENE_MEMORY_MANAGER_TYPES];
    GameObjectsVec const* m_threadGameObjectsToUpdate;
    float m_threadWeight;

    bool m_quit;
    bool m_alwaysAskForConfig;
    bool m_useHlmsDiskCache;
    bool m_useMicrocodeCache;

    Ogre::ColourValue m_backgroundColour;
};