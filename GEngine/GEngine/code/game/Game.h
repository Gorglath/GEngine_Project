#pragma once
#include "Ogre.h"
#include "OgreItem.h"
#include "OgreSceneManager.h"
#include "OgreMeshManager2.h"
#include "../engine/GraphicSystem.hpp"
#include "TutorialGameState.h"

using namespace Ogre;
class Game : public GameState
{
public:
	void init(GraphicSystem* graphicSystem);
	virtual void createScene01() override;
	virtual void update(float dt) override;
protected:
	virtual void createFloor();
	virtual void createLight();
	SceneManager* m_sceneManager;
	Item* m_floor;
};

