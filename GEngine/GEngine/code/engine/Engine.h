#pragma once

#include "GameState.h"
#include "GraphicSystem.h"
#include "SoundSystem.h"
#include "Time.h"
#include "InputData.hpp"

class Engine
{
public:
	Engine()  =default;
	~Engine();
	void init(GameState& gameState);
	bool loadScene();
	bool update();
	void clean();
	GraphicSystem m_graphicsSystem;
	SoundSystem m_soundSystem;
private:
	Time m_time;
};

