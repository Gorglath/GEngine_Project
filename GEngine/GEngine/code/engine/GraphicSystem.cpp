
#include "GraphicSystem.h"
#include "GameState.h"
#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE_IOS
#include "SdlInputHandler.h"
#endif
#include "GameObject.h"

#include "OgreConfigFile.h"
#include "OgreException.h"
#include "OgreRoot.h"

#include "OgreCamera.h"
#include "OgreItem.h"

#include "OgreArchiveManager.h"
#include "OgreHlmsManager.h"

#include "Compositor/OgreCompositorManager2.h"

#include "OgreOverlayManager.h"
#include "OgreOverlaySystem.h"

#include "OgreTextureGpuManager.h"
#include "OgreHlmsPbs.h"
#include "OgreHlmsUnlit.h"

#include "OgreWindow.h"
#include "OgreWindowEventUtilities.h"

#include "OgreFileSystemLayer.h"

#include "OgreGpuProgramManager.h"
#include "OgreHlmsDiskCache.h"

#include "OgreLogManager.h"

#include "OgrePlatformInformation.h"

#include <fstream>

#include <SDL_syswm.h>

GraphicSystem::GraphicSystem(GameState* gameState, Ogre::String resourcePath,
        Ogre::ColourValue backgroundColour) :
        BaseSystem(gameState),
        m_logicSystem(0),
        m_sdlWindow(0),
        m_inputHandler(0),
        m_root(0),
        m_renderWindow(0),
        m_sceneManager(0),
        m_camera(0),
        m_workspace(0),
        m_pluginsFolder("./"),
        m_resourcePath(resourcePath),
        m_overlaySystem(0),
        m_accumTimeSinceLastLogicFrame(0),
        m_currentTransformIdx(0),
        m_threadGameObjectsToUpdate(0),
        m_threadWeight(0),
        m_quit(false),
        m_alwaysAskForConfig(true),
        m_useHlmsDiskCache(true),
        m_useMicrocodeCache(true),
        m_backgroundColour(backgroundColour)
    {
        if (isWriteAccessFolder(m_pluginsFolder, "Ogre.log"))
            m_writeAccessFolder = m_pluginsFolder;
        else
        {
            Ogre::FileSystemLayer filesystemLayer(OGRE_VERSION_NAME);
            m_writeAccessFolder = filesystemLayer.getWritablePath("");
        }
    }
    //-----------------------------------------------------------------------------------
    GraphicSystem::~GraphicSystem()
    {
        if (m_root)
        {
            Ogre::LogManager::getSingleton().logMessage(
                "WARNING: GraphicSystem::deinitialize() not called!!!", Ogre::LML_CRITICAL);
        }
    }
    //-----------------------------------------------------------------------------------
    bool GraphicSystem::isWriteAccessFolder(const Ogre::String& folderPath,
        const Ogre::String& fileToSave)
    {
        if (!Ogre::FileSystemLayer::createDirectory(folderPath))
            return false;

        std::ofstream of((folderPath + fileToSave).c_str(),
            std::ios::out | std::ios::binary | std::ios::app);
        if (!of)
            return false;

        return true;
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::initialize(const Ogre::String& windowTitle)
    {
        // if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
        if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER |
            SDL_INIT_EVENTS) != 0)
        {
            OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!",
                "GraphicSystem::initialize");
        }
        Ogre::String pluginsPath;
        // only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
#    if OGRE_DEBUG_MODE && \
        !( ( OGRE_PLATFORM == OGRE_PLATFORM_APPLE ) || ( OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS ) )
        pluginsPath = m_pluginsFolder + "plugins_d.cfg";
#    else
        pluginsPath = m_pluginsFolder + "plugins.cfg";
#    endif
#endif

#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
        const Ogre::String cfgPath = m_writeAccessFolder + "ogre.cfg";
#endif

        m_root =
            OGRE_NEW Ogre::Root(pluginsPath, cfgPath, m_writeAccessFolder + "Ogre.log", windowTitle);
        
        m_staticPluginLoader.install(m_root);

        // enable sRGB Gamma Conversion mode by default for all renderers,
        // but still allow to override it via config dialog
        Ogre::RenderSystemList::const_iterator itor = m_root->getAvailableRenderers().begin();
        Ogre::RenderSystemList::const_iterator endt = m_root->getAvailableRenderers().end();

        while (itor != endt)
        {
            Ogre::RenderSystem* rs = *itor;
            rs->setConfigOption("sRGB Gamma Conversion", "Yes");
            ++itor;
        }

        if (m_alwaysAskForConfig || !m_root->restoreConfig())
        {
            if (!m_root->showConfigDialog())
            {
                m_quit = true;
                return;
            }
        }

        m_root->initialise(false, windowTitle);

        Ogre::ConfigOptionMap& cfgOpts = m_root->getRenderSystem()->getConfigOptions();

        int width = 1280;
        int height = 720;

        Ogre::ConfigOptionMap::iterator opt = cfgOpts.find("Video Mode");
        if (opt != cfgOpts.end() && !opt->second.currentValue.empty())
        {
            // Ignore leading space
            const Ogre::String::size_type start = opt->second.currentValue.find_first_of("012356789");
            // Get the width and height
            Ogre::String::size_type widthEnd = opt->second.currentValue.find(' ', start);
            // we know that the height starts 3 characters after the width and goes until the next space
            Ogre::String::size_type heightEnd = opt->second.currentValue.find(' ', widthEnd + 3);
            // Now we can parse out the values
            width = Ogre::StringConverter::parseInt(opt->second.currentValue.substr(0, widthEnd));
            height = Ogre::StringConverter::parseInt(
                opt->second.currentValue.substr(widthEnd + 3, heightEnd));
        }

        Ogre::NameValuePairList params;
        bool fullscreen = Ogre::StringConverter::parseBool(cfgOpts["Full Screen"].currentValue);

        unsigned int screen = 0;
        unsigned int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
        unsigned int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

        if (fullscreen)
        {
            posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
            posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
        }

        m_sdlWindow = SDL_CreateWindow(
            windowTitle.c_str(),       // window title
            static_cast<int>(posX),  // initial x position
            static_cast<int>(posY),  // initial y position
            width,                     // width, in pixels
            height,                    // height, in pixels
            SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);

        // Get the native whnd
        SDL_SysWMinfo wmInfo;
        SDL_VERSION(&wmInfo.version);

        if (SDL_GetWindowWMInfo(m_sdlWindow, &wmInfo) == SDL_FALSE)
        {
            OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Couldn't get WM Info! (SDL2)",
                "GraphicSystem::initialize");
        }

        Ogre::String winHandle;
        switch (wmInfo.subsystem)
        {
#    if defined( SDL_VIDEO_DRIVER_WINDOWS )
        case SDL_SYSWM_WINDOWS:
            // Windows code
            winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.win.window);
            break;
#    endif
#    if defined( SDL_VIDEO_DRIVER_WINRT )
        case SDL_SYSWM_WINRT:
            // Windows code
            winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.winrt.window);
            break;
#    endif
#    if defined( SDL_VIDEO_DRIVER_COCOA )
        case SDL_SYSWM_COCOA:
            winHandle = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
            break;
#    endif
#    if defined( SDL_VIDEO_DRIVER_X11 )
        case SDL_SYSWM_X11:
            winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.x11.window);
            params.insert(std::make_pair(
                "SDL2x11", Ogre::StringConverter::toString((uintptr_t)&wmInfo.info.x11)));
            break;
#    endif
        default:
            OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED, "Unexpected WM! (SDL2)",
                "GraphicSystem::initialize");
            break;
        }

#    if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
        params.insert(std::make_pair("externalWindowHandle", winHandle));
#    else
        params.insert(std::make_pair("parentWindowHandle", winHandle));
#    endif

        params.insert(std::make_pair("title", windowTitle));
        params.insert(std::make_pair("gamma", cfgOpts["sRGB Gamma Conversion"].currentValue));
        if (cfgOpts.find("VSync Method") != cfgOpts.end())
            params.insert(std::make_pair("vsync_method", cfgOpts["VSync Method"].currentValue));
        params.insert(std::make_pair("FSAA", cfgOpts["FSAA"].currentValue));
        params.insert(std::make_pair("vsync", cfgOpts["VSync"].currentValue));
        params.insert(std::make_pair("reverse_depth", "Yes"));

        initMiscParamsListener(params);

        m_renderWindow = Ogre::Root::getSingleton().createRenderWindow(
            windowTitle,                                                      //
            static_cast<uint32_t>(width), static_cast<uint32_t>(height),  //
            fullscreen, &params);

        m_overlaySystem = OGRE_NEW Ogre::v1::OverlaySystem();

        setupResources();
        loadResources();
        chooseSceneManager();
        createCamera();
        m_workspace = setupCompositor();

        m_inputHandler =
            new SdlInputHandler(m_sdlWindow, m_currentGameState, m_currentGameState, m_currentGameState);

        BaseSystem::initialize();

#if OGRE_PROFILING
        Ogre::Profiler::getSingleton().setEnabled(true);
#    if OGRE_PROFILING == OGRE_PROFILING_INTERNAL
        Ogre::Profiler::getSingleton().endProfile("");
#    endif
#    if OGRE_PROFILING == OGRE_PROFILING_INTERNAL_OFFLINE
        Ogre::Profiler::getSingleton().getOfflineProfiler().setDumpPathsOnShutdown(
            m_writeAccessFolder + "ProfilePerFrame", m_writeAccessFolder + "ProfileAccum");
#    endif
#endif
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::deinitialize()
    {
        BaseSystem::deinitialize();

        saveTextureCache();
        saveHlmsDiskCache();

        if (m_sceneManager)
            m_sceneManager->removeRenderQueueListener(m_overlaySystem);

        OGRE_DELETE m_overlaySystem;
        m_overlaySystem = 0;

        delete m_inputHandler;
        m_inputHandler = 0;

        OGRE_DELETE m_root;
        m_root = 0;

        if (m_sdlWindow)
        {
            // Restore desktop resolution on exit
            SDL_SetWindowFullscreen(m_sdlWindow, 0);
            SDL_DestroyWindow(m_sdlWindow);
            m_sdlWindow = 0;
        }

        SDL_Quit();
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::update(float timeSinceLast)
    {
        Ogre::WindowEventUtilities::messagePump();

        SDL_Event evt;
        while (SDL_PollEvent(&evt))
        {
            switch (evt.type)
            {
            case SDL_WINDOWEVENT:
                handleWindowEvent(evt);
                break;
            case SDL_QUIT:
                m_quit = true;
                break;
            default:
                break;
            }

            m_inputHandler->_handleSdlEvents(evt);
        }

        BaseSystem::update(timeSinceLast);

        if (m_renderWindow->isVisible())
            m_quit |= !m_root->renderOneFrame();

        m_accumTimeSinceLastLogicFrame += timeSinceLast;

    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::handleWindowEvent(const SDL_Event& evt)
    {
        switch (evt.window.event)
        {
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            int w, h;
            SDL_GetWindowSize(m_sdlWindow, &w, &h);
            m_renderWindow->windowMovedOrResized();
            break;
        case SDL_WINDOWEVENT_CLOSE:
            break;
        case SDL_WINDOWEVENT_SHOWN:
            m_renderWindow->_setVisible(true);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            m_renderWindow->_setVisible(false);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            m_renderWindow->setFocused(true);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            m_renderWindow->setFocused(false);
            break;
        }
    }

    //-----------------------------------------------------------------------------------
    void GraphicSystem::processIncomingMessage(MessageId messageId, const void* data)
    {
        switch (messageId)
        {
        case LOGICFRAME_FINISHED:
        {
            Ogre::uint32 newIdx = *reinterpret_cast<const Ogre::uint32*>(data);

            if (newIdx != std::numeric_limits<Ogre::uint32>::max())
            {
                m_accumTimeSinceLastLogicFrame = 0;
                // Tell the LogicSystem we're no longer using the index previous to the current one.
                this->queueSendMessage(
                    m_logicSystem, LOGICFRAME_FINISHED,
                    (m_currentTransformIdx + 4 - 1) % 4);

                assert((m_currentTransformIdx + 1) % 4 == newIdx &&
                    "Graphics is receiving indices out of order!!!");

                // Get the new index the LogicSystem is telling us to use.
                m_currentTransformIdx = newIdx;
            }
        }
        break;
        case GAME_OBJECT_ADDED:
            gameObjectAdded(reinterpret_cast<const GameObjectManager::CreatedGameObject*>(data));
            break;
        case GAME_OBJECT_REMOVED:
            gameObjectRemove(*reinterpret_cast<GameObject* const*>(data));
            break;
        case GAME_OBJECT_SCHEDULED_FOR_REMOVAL_SLOT:
            // Acknowledge/notify back that we're done with this slot.
            this->queueSendMessage(m_logicSystem, GAME_OBJECT_SCHEDULED_FOR_REMOVAL_SLOT,
                *reinterpret_cast<const Ogre::uint32*>(data));
            break;
        default:
            break;
        }
    }
    
    void GraphicSystem::loadTextureCache()
    {
#if !OGRE_NO_JSON
        Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();
        Ogre::Archive* rwAccessFolderArchive =
            archiveManager.load(m_writeAccessFolder, "FileSystem", true);
        try
        {
            const Ogre::String filename = "textureMetadataCache.json";
            if (rwAccessFolderArchive->exists(filename))
            {
                Ogre::DataStreamPtr stream = rwAccessFolderArchive->open(filename);
                std::vector<char> fileData;
                fileData.resize(stream->size() + 1);
                if (!fileData.empty())
                {
                    stream->read(&fileData[0], stream->size());
                    // Add null terminator just in case (to prevent bad input)
                    fileData.back() = '\0';
                    Ogre::TextureGpuManager* textureManager =
                        m_root->getRenderSystem()->getTextureGpuManager();
                    textureManager->importTextureMetadataCache(stream->getName(), &fileData[0], false);
                }
            }
            else
            {
                Ogre::LogManager::getSingleton().logMessage("[INFO] Texture cache not found at " +
                    m_writeAccessFolder +
                    "/textureMetadataCache.json");
            }
        }
        catch (Ogre::Exception& e)
        {
            Ogre::LogManager::getSingleton().logMessage(e.getFullDescription());
        }

        archiveManager.unload(rwAccessFolderArchive);
#endif
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::saveTextureCache()
    {
        if (m_root->getRenderSystem())
        {
            Ogre::TextureGpuManager* textureManager = m_root->getRenderSystem()->getTextureGpuManager();
            if (textureManager)
            {
                Ogre::String jsonString;
                textureManager->exportTextureMetadataCache(jsonString);
                const Ogre::String path = m_writeAccessFolder + "/textureMetadataCache.json";
                std::ofstream file(path.c_str(), std::ios::binary | std::ios::out);
                if (file.is_open())
                    file.write(jsonString.c_str(), static_cast<std::streamsize>(jsonString.size()));
                file.close();
            }
        }
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::loadHlmsDiskCache()
    {
        if (!m_useMicrocodeCache && !m_useHlmsDiskCache)
            return;

        Ogre::HlmsManager* hlmsManager = m_root->getHlmsManager();
        Ogre::HlmsDiskCache diskCache(hlmsManager);

        Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();

        Ogre::Archive* rwAccessFolderArchive =
            archiveManager.load(m_writeAccessFolder, "FileSystem", true);

        if (m_useMicrocodeCache)
        {
            // Make sure the microcode cache is enabled.
            Ogre::GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true);
            const Ogre::String filename = "microcodeCodeCache.cache";
            if (rwAccessFolderArchive->exists(filename))
            {
                Ogre::DataStreamPtr shaderCacheFile = rwAccessFolderArchive->open(filename);
                Ogre::GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);
            }
        }

        if (m_useHlmsDiskCache)
        {
            for (size_t i = Ogre::HLMS_LOW_LEVEL + 1u; i < Ogre::HLMS_MAX; ++i)
            {
                Ogre::Hlms* hlms = hlmsManager->getHlms(static_cast<Ogre::HlmsTypes>(i));
                if (hlms)
                {
                    Ogre::String filename =
                        "hlmsDiskCache" + Ogre::StringConverter::toString(i) + ".bin";

                    try
                    {
                        if (rwAccessFolderArchive->exists(filename))
                        {
                            Ogre::DataStreamPtr diskCacheFile = rwAccessFolderArchive->open(filename);
                            diskCache.loadFrom(diskCacheFile);
                            diskCache.applyTo(hlms);
                        }
                    }
                    catch (Ogre::Exception&)
                    {
                        Ogre::LogManager::getSingleton().logMessage(
                            "Error loading cache from " + m_writeAccessFolder + "/" + filename +
                            "! If you have issues, try deleting the file "
                            "and restarting the app");
                    }
                }
            }
        }

        archiveManager.unload(m_writeAccessFolder);
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::saveHlmsDiskCache()
    {
        if (m_root->getRenderSystem() && Ogre::GpuProgramManager::getSingletonPtr() &&
            (m_useMicrocodeCache || m_useHlmsDiskCache))
        {
            Ogre::HlmsManager* hlmsManager = m_root->getHlmsManager();
            Ogre::HlmsDiskCache diskCache(hlmsManager);

            Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();

            Ogre::Archive* rwAccessFolderArchive =
                archiveManager.load(m_writeAccessFolder, "FileSystem", false);

            if (m_useHlmsDiskCache)
            {
                for (size_t i = Ogre::HLMS_LOW_LEVEL + 1u; i < Ogre::HLMS_MAX; ++i)
                {
                    Ogre::Hlms* hlms = hlmsManager->getHlms(static_cast<Ogre::HlmsTypes>(i));
                    if (hlms)
                    {
                        diskCache.copyFrom(hlms);

                        Ogre::DataStreamPtr diskCacheFile = rwAccessFolderArchive->create(
                            "hlmsDiskCache" + Ogre::StringConverter::toString(i) + ".bin");
                        diskCache.saveTo(diskCacheFile);
                    }
                }
            }

            if (Ogre::GpuProgramManager::getSingleton().isCacheDirty() && m_useMicrocodeCache)
            {
                const Ogre::String filename = "microcodeCodeCache.cache";
                Ogre::DataStreamPtr shaderCacheFile = rwAccessFolderArchive->create(filename);
                Ogre::GpuProgramManager::getSingleton().saveMicrocodeCache(shaderCacheFile);
            }

            archiveManager.unload(m_writeAccessFolder);
        }
    }
    void GraphicSystem::registerHlms()
    {
        Ogre::ConfigFile cf;
        cf.load(m_resourcePath + "resources2.cfg");

        Ogre::String rootHlmsFolder = m_resourcePath + cf.getSetting("DoNotUseAsResource", "Hlms", "");

        if (*(rootHlmsFolder.end() - 1) != '/')
            rootHlmsFolder += "/";

        Ogre::HlmsUnlit* hlmsUnlit = 0;
        Ogre::HlmsPbs* hlmsPbs = 0;
        // For retrieval of the paths to the different folders needed
        Ogre::String mainFolderPath;
        Ogre::StringVector libraryFoldersPaths;
        Ogre::StringVector::const_iterator libraryFolderPathIt;
        Ogre::StringVector::const_iterator libraryFolderPathEn;

        Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();

        const Ogre::String& archiveType = getMediaReadArchiveType();

        {
            // Create & Register HlmsUnlit
            // Get the path to all the subdirectories used by HlmsUnlit
            Ogre::HlmsUnlit::getDefaultPaths(mainFolderPath, libraryFoldersPaths);
            Ogre::Archive* archiveUnlit =
                archiveManager.load(rootHlmsFolder + mainFolderPath, archiveType, true);
            Ogre::ArchiveVec archiveUnlitLibraryFolders;
            libraryFolderPathIt = libraryFoldersPaths.begin();
            libraryFolderPathEn = libraryFoldersPaths.end();
            while (libraryFolderPathIt != libraryFolderPathEn)
            {
                Ogre::Archive* archiveLibrary =
                    archiveManager.load(rootHlmsFolder + *libraryFolderPathIt, archiveType, true);
                archiveUnlitLibraryFolders.push_back(archiveLibrary);
                ++libraryFolderPathIt;
            }

            // Create and register the unlit Hlms
            hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &archiveUnlitLibraryFolders);
            Ogre::Root::getSingleton().getHlmsManager()->registerHlms(dynamic_cast<Hlms*>(hlmsUnlit));
        }

        {
            // Create & Register HlmsPbs
            // Do the same for HlmsPbs:
            Ogre::HlmsPbs::getDefaultPaths(mainFolderPath, libraryFoldersPaths);
            Ogre::Archive* archivePbs =
                archiveManager.load(rootHlmsFolder + mainFolderPath, archiveType, true);

            // Get the library archive(s)
            Ogre::ArchiveVec archivePbsLibraryFolders;
            libraryFolderPathIt = libraryFoldersPaths.begin();
            libraryFolderPathEn = libraryFoldersPaths.end();
            while (libraryFolderPathIt != libraryFolderPathEn)
            {
                Ogre::Archive* archiveLibrary =
                    archiveManager.load(rootHlmsFolder + *libraryFolderPathIt, archiveType, true);
                archivePbsLibraryFolders.push_back(archiveLibrary);
                ++libraryFolderPathIt;
            }

            // Create and register
            hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &archivePbsLibraryFolders);
            Ogre::Root::getSingleton().getHlmsManager()->registerHlms(dynamic_cast<Hlms*>(hlmsPbs));
        }

        Ogre::RenderSystem* renderSystem = m_root->getRenderSystem();
        if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
        {
            // Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
            // and below to avoid saturating AMD's discard limit (8MB) or
            // saturate the PCIE bus in some low end machines.
            bool supportsNoOverwriteOnTextureBuffers;
            renderSystem->getCustomAttribute("MapNoOverwriteOnDynamicBufferSRV",
                &supportsNoOverwriteOnTextureBuffers);

            if (!supportsNoOverwriteOnTextureBuffers)
            {
                hlmsPbs->setTextureBufferDefaultSize(512 * 1024);
                hlmsUnlit->setTextureBufferDefaultSize(512 * 1024);
            }
        }
    }
    void GraphicSystem::setupResources()
    {
        // Load resource paths from config file
        Ogre::ConfigFile cf;
        cf.load(m_resourcePath + "resources2.cfg");

        // Go through all sections & settings in the file
        Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

        Ogre::String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();

            if (secName != "Hlms")
            {
                Ogre::ConfigFile::SettingsMultiMap::iterator i;
                for (i = settings->begin(); i != settings->end(); ++i)
                {
                    typeName = i->first;
                    archName = i->second;
                    addResourceLocation(archName, typeName, secName);
                }
            }
        }
    }
    void GraphicSystem::loadResources()
    {
        registerHlms();

        loadTextureCache();
        loadHlmsDiskCache();

        // Initialise, parse scripts etc
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(true);

        // Initialize resources for LTC area lights and accurate specular reflections (IBL)
        Ogre::Hlms* hlms = m_root->getHlmsManager()->getHlms(Ogre::HLMS_PBS);
        OGRE_ASSERT_HIGH(dynamic_cast<Ogre::HlmsPbs*>(hlms));
        Ogre::HlmsPbs* hlmsPbs = static_cast<Ogre::HlmsPbs*>(hlms);
        try
        {
            hlmsPbs->loadLtcMatrix();
        }
        catch (Ogre::FileNotFoundException& e)
        {
            Ogre::LogManager::getSingleton().logMessage(e.getFullDescription(), Ogre::LML_CRITICAL);
            Ogre::LogManager::getSingleton().logMessage(
                "WARNING: LTC matrix textures could not be loaded. Accurate specular IBL reflections "
                "and LTC area lights won't be available or may not function properly!",
                Ogre::LML_CRITICAL);
        }
    }
    void GraphicSystem::addResourceLocation(const Ogre::String& archName, const Ogre::String& typeName,
        const Ogre::String& secName)
    {
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::chooseSceneManager()
    {
#if OGRE_DEBUG_MODE >= OGRE_DEBUG_HIGH
        // Debugging multithreaded code is a PITA, disable it.
        const size_t numThreads = 1;
#else
        // getNumLogicalCores() may return 0 if couldn't detect
        const size_t numThreads = std::max<size_t>(1, Ogre::PlatformInformation::getNumLogicalCores());
#endif
        // Create the SceneManager, in this case a generic one
        m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC, numThreads, "ExampleSMInstance");

        m_sceneManager->addRenderQueueListener(m_overlaySystem);
        m_sceneManager->getRenderQueue()->setSortRenderQueue(
            Ogre::v1::OverlayManager::getSingleton().mDefaultRenderQueueId,
            Ogre::RenderQueue::StableSort);

        // Set sane defaults for proper shadow mapping
        m_sceneManager->setShadowDirectionalLightExtrusionDistance(500.0f);
        m_sceneManager->setShadowFarDistance(500.0f);
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::createCamera()
    {
        m_camera = m_sceneManager->createCamera("Main Camera");

        // Position it at 500 in Z direction
        m_camera->setPosition(Ogre::Vector3(0, 20, 0));
        // Look back along -Z
        m_camera->lookAt(Ogre::Vector3(0, 0, 0));
        m_camera->rotate(Ogre::Vector3(0, 1, 0), Radian(Degree(90.0f)));
        m_camera->setNearClipDistance(0.2f);
        m_camera->setFarClipDistance(1000.0f);
        m_camera->setAutoAspectRatio(true);
    }
    //-----------------------------------------------------------------------------------
    Ogre::CompositorWorkspace* GraphicSystem::setupCompositor()
    {
        Ogre::CompositorManager2* compositorManager = m_root->getCompositorManager2();

        const Ogre::String workspaceName("Demo Workspace");
        if (!compositorManager->hasWorkspaceDefinition(workspaceName))
        {
            compositorManager->createBasicWorkspaceDef(workspaceName, m_backgroundColour,
                Ogre::IdString());
        }

        return compositorManager->addWorkspace(m_sceneManager, m_renderWindow->getTexture(), m_camera,
            workspaceName, true);
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::initMiscParamsListener(Ogre::NameValuePairList& params) {}
    //-----------------------------------------------------------------------------------
    const char* GraphicSystem::getMediaReadArchiveType() const
    {
#if OGRE_PLATFORM != OGRE_PLATFORM_ANDROID
        return "FileSystem";
#else
        return "APKFileSystem";
#endif
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::stopCompositor()
    {
        if (m_workspace)
        {
            Ogre::CompositorManager2* compositorManager = m_root->getCompositorManager2();
            compositorManager->removeWorkspace(m_workspace);
            m_workspace = 0;
        }
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::restartCompositor()
    {
        stopCompositor();
        m_workspace = setupCompositor();
    }
    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------
    struct GameObjectCmp
    {
        bool operator()(const GameObject* _l, const Ogre::Matrix4* RESTRICT_ALIAS _r) const
        {
            const Ogre::Transform& transform = _l->m_sceneNode->_getTransform();
            return &transform.mDerivedTransform[transform.mIndex] < _r;
        }

        bool operator()(const Ogre::Matrix4* RESTRICT_ALIAS _r, const GameObject* _l) const
        {
            const Ogre::Transform& transform = _l->m_sceneNode->_getTransform();
            return _r < &transform.mDerivedTransform[transform.mIndex];
        }

        bool operator()(const GameObject* _l, const GameObject* _r) const
        {
            const Ogre::Transform& lTransform = _l->m_sceneNode->_getTransform();
            const Ogre::Transform& rTransform = _r->m_sceneNode->_getTransform();
            return &lTransform.mDerivedTransform[lTransform.mIndex] <
                &rTransform.mDerivedTransform[rTransform.mIndex];
        }
    };
    //-----------------------------------------------------------------------------------
    void GraphicSystem::gameObjectAdded(const GameObjectManager::CreatedGameObject* cge)
    {
        Ogre::SceneNode* sceneNode =
            m_sceneManager->getRootSceneNode(cge->m_gameObject->m_type)
            ->createChildSceneNode(cge->m_gameObject->m_type, cge->m_initialTransform.m_vPos,
                cge->m_initialTransform.m_qRot);

        sceneNode->setScale(cge->m_initialTransform.m_vScale);

        cge->m_gameObject->m_sceneNode = sceneNode;

        if (cge->m_gameObject->m_moDefinition->m_moType == MoTypeItem)
        {
            Ogre::Item* item = m_sceneManager->createItem(cge->m_gameObject->m_moDefinition->m_meshName,
                cge->m_gameObject->m_moDefinition->m_resourceGroup,
                cge->m_gameObject->m_type);

            Ogre::StringVector materialNames = cge->m_gameObject->m_moDefinition->m_submeshMaterials;
            size_t minMaterials = std::min(materialNames.size(), item->getNumSubItems());

            for (size_t i = 0; i < minMaterials; ++i)
            {
                item->getSubItem(i)->setDatablockOrMaterialName(
                    materialNames[i], cge->m_gameObject->m_moDefinition->m_resourceGroup);
            }

            cge->m_gameObject->m_movableObject = item;
        }

        sceneNode->attachObject(cge->m_gameObject->m_movableObject);

        // Keep them sorted on how Ogre's internal memory manager assigned them memory,
        // to avoid false cache sharing when we update the nodes concurrently.
        const Ogre::Transform& transform = sceneNode->_getTransform();
        GameObjectsVec::iterator itGameObject = std::lower_bound(
            m_gameObjects[cge->m_gameObject->m_type].begin(), m_gameObjects[cge->m_gameObject->m_type].end(),
            &transform.mDerivedTransform[transform.mIndex], GameObjectCmp());
        m_gameObjects[cge->m_gameObject->m_type].insert(itGameObject, cge->m_gameObject);
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::gameObjectRemove(GameObject* toRemove)
    {
        const Ogre::Transform& transform = toRemove->m_sceneNode->_getTransform();
        GameObjectsVec::iterator itGameObject = std::lower_bound(
            m_gameObjects[toRemove->m_type].begin(), m_gameObjects[toRemove->m_type].end(),
            &transform.mDerivedTransform[transform.mIndex], GameObjectCmp());

        assert(itGameObject != m_gameObjects[toRemove->m_type].end() && *itGameObject == toRemove);
        m_gameObjects[toRemove->m_type].erase(itGameObject);

        toRemove->m_sceneNode->getParentSceneNode()->removeAndDestroyChild(toRemove->m_sceneNode);
        toRemove->m_sceneNode = 0;

        assert(dynamic_cast<Ogre::Item*>(toRemove->m_movableObject));

        m_sceneManager->destroyItem(static_cast<Ogre::Item*>(toRemove->m_movableObject));
        toRemove->m_movableObject = 0;
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::updateGameObjects(const GameObjectsVec& gameObjects, float weight)
    {
        m_threadGameObjectsToUpdate = &gameObjects;
        m_threadWeight = weight;

        // Note: You could execute a non-blocking scalable task and do something else, you should
        // wait for the task to finish right before calling renderOneFrame or before trying to
        // execute another UserScalableTask (you would have to be careful, but it could work).
        m_sceneManager->executeUserScalableTask(this, true);
    }
    //-----------------------------------------------------------------------------------
    void GraphicSystem::execute(size_t threadId, size_t numThreads)
    {
        size_t currIdx = m_currentTransformIdx;
        size_t prevIdx =
            (m_currentTransformIdx + 4 - 1) % 4;

        const size_t objsPerThread =
            (m_threadGameObjectsToUpdate->size() + (numThreads - 1)) / numThreads;
        const size_t toAdvance = std::min(threadId * objsPerThread, m_threadGameObjectsToUpdate->size());

        GameObjectsVec::const_iterator itor =
            m_threadGameObjectsToUpdate->begin() + static_cast<ptrdiff_t>(toAdvance);
        GameObjectsVec::const_iterator end =
            m_threadGameObjectsToUpdate->begin() +
            static_cast<ptrdiff_t>(
                std::min(toAdvance + objsPerThread, m_threadGameObjectsToUpdate->size()));
        while (itor != end)
        {
            GameObject* gEnt = *itor;
            Ogre::Vector3 interpVec = Ogre::Math::lerp(gEnt->m_transform[prevIdx]->m_vPos,
                gEnt->m_transform[currIdx]->m_vPos, m_threadWeight);
            gEnt->m_sceneNode->setPosition(interpVec);

            interpVec = Ogre::Math::lerp(gEnt->m_transform[prevIdx]->m_vScale,
                gEnt->m_transform[currIdx]->m_vScale, m_threadWeight);
            gEnt->m_sceneNode->setScale(interpVec);

            Ogre::Quaternion interpQ = Ogre::Quaternion::nlerp(
                m_threadWeight, gEnt->m_transform[prevIdx]->m_qRot, gEnt->m_transform[currIdx]->m_qRot, true);
            gEnt->m_sceneNode->setOrientation(interpQ);

            ++itor;
        }
    }
