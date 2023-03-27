#pragma once
#include "Ogre.h"
#include "OgreItem.h"
#include "OgreSceneManager.h"
#include "OgreMeshManager2.h"
#include "../engine/GraphicSystem.h"
#include "../engine/GameState.h"
#include "../engine/GameEntity.h"
#include <vector>
using namespace Ogre;
namespace GEngine
{
	class Game : public GameState
	{
	public:
		void init(GraphicSystem* graphicSystem);
		virtual void createScene01() override;
		virtual void update(float dt) override;
		virtual void destroyScene() override;
	protected:
		virtual void createFloor();
		virtual void createLight();
		SceneManager* m_sceneManager;
		GameEntity m_floor;
		std::vector<GameEntity> m_gameEntities{};
	};
}
