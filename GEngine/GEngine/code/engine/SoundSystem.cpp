#include "SoundSystem.h"

bool SoundSystem::intialize(std::string audioDirectoryPath)
{
	m_audioDirectoryPath = audioDirectoryPath;
	m_engine = createIrrKlangDevice();

	if (!m_engine)
		return false;

	return true;
}

void SoundSystem::play2DSound(std::string name, bool shouldLoop)
{
	std::string audioPath = m_audioDirectoryPath + '\\' + name;
	m_engine->play2D(audioPath.c_str(), shouldLoop);
}

void SoundSystem::destroy()
{
	m_engine->drop();
}
