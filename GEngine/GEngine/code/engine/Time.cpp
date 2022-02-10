#include "Time.h"

double Time::m_dt;
void Time::init()
{
    Ogre::Timer timer;
    Ogre::uint64 startTime = timer.getMicroseconds();

    double m_dt = 1.0 / 60.0;
}

void Time::update()
{
    Ogre::uint64 endTime = timer.getMicroseconds();
    m_dt = (endTime - startTime) / 1000000.0;
    m_dt = std::min(1.0, m_dt);  // Prevent from going haywire.
    startTime = endTime;

}
