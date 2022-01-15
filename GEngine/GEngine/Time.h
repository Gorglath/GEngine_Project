#pragma once

#include "OgreTimer.h"
class Time
{
public:
	void init();
	void update();
	static double getDeltaTime() { return m_dt; };
private:
	static double m_dt;
	Ogre::uint64 startTime;
    Ogre::Timer timer;
};

