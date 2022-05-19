#include <irrKlang.h>
#include <string>
using namespace irrklang;
#pragma once
class SoundSystem
{
public:
	bool intialize(std::string audioDirectoryPath);
	void play2DSound(std::string name, bool shouldLoop);
	void destroy();
private:
	ISoundEngine* m_engine = nullptr;
	std::string m_audioDirectoryPath = "";
};

