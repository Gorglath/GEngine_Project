#pragma once

#include "OgreCamera.h"
#include "OgreRoot.h"

#include "OgreWindowEventUtilities.h"

#include "Compositor/OgreCompositorManager2.h"

#include "WindowEventListener.hpp"
using namespace Ogre;

class Engine
{
public:
	Engine() = default;
	~Engine();
	void init();
	bool update();
	void clean();

	bool getWindowQuit() const { return m_windowEventListener.getQuit(); }
private:
	Root* m_root = nullptr;
	Window* m_window = nullptr;
	MyWindowEventListener m_windowEventListener;
};

