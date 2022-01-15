#include "Engine.h"

Engine::~Engine()
{
    clean();
}

void Engine::init()
{
    const String pluginsFolder = "";
    const String writeAccessFolder = pluginsFolder;

    const char* pluginsFile = nullptr;

    m_root = OGRE_NEW Root();

    m_root->showConfigDialog();

    // Initialize Root
    m_root->getRenderSystem()->setConfigOption("sRGB Gamma Conversion", "Yes");
    Window* window = m_root->initialise(true, "Tutorial 00: Basic");

    //registerHlms();

    // Create SceneManager
    const size_t numThreads = 1u;
    SceneManager* sceneManager = m_root->createSceneManager(ST_GENERIC, numThreads, "ExampleSMInstance");

    // Create & setup camera
    Camera* camera = sceneManager->createCamera("Main Camera");

    // Position it at 500 in Z direction
    camera->setPosition(Vector3(0, 5, 15));
    // Look back along -Z
    camera->lookAt(Vector3(0, 0, 0));
    camera->setNearClipDistance(0.2f);
    camera->setFarClipDistance(1000.0f);
    camera->setAutoAspectRatio(true);

    // Setup a basic compositor with a blue clear colour
    CompositorManager2* compositorManager = m_root->getCompositorManager2();
    const String workspaceName("Demo Workspace");
    const ColourValue backgroundColour(0.2f, 0.4f, 0.6f);
    compositorManager->createBasicWorkspaceDef(workspaceName, backgroundColour, IdString());
    compositorManager->addWorkspace(sceneManager, window->getTexture(), camera, workspaceName, true);

    WindowEventUtilities::addWindowEventListener(window, &m_windowEventListener);
}

bool Engine::update()
{
    WindowEventUtilities::messagePump();
    return m_root->renderOneFrame();
}

void Engine::clean()
{
    WindowEventUtilities::removeWindowEventListener(m_window, &m_windowEventListener);

    OGRE_DELETE m_root;
    m_root = 0;
}
