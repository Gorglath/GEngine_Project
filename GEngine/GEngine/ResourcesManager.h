#pragma once

#include "OgreArchiveManager.h"
#include "OgreConfigFile.h"

#include "OgreHlmsManager.h"
#include "OgreHlmsPbs.h"
#include "OgreHlmsUnlit.h"

class ResourcesManager
{
public:
	void init();
private:
	void registerHsml();
};

