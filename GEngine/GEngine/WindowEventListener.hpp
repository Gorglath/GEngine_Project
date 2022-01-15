#pragma once

#include "OgreWindow.h"

#include "OgreWindowEventUtilities.h"

class MyWindowEventListener final : public Ogre::WindowEventListener
{
public:
    MyWindowEventListener() : m_quit(false) {}
    void windowClosed(Ogre::Window* rw) override { m_quit = true; }

    bool getQuit() const { return m_quit; }
private:
    bool m_quit = false;
};