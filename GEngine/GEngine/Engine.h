#pragma once

#include "GameState.h"
#include "GraphicSystem.hpp"
#include "Time.h"
using namespace Demo;

class Engine
{
public:
	Engine()  =default;
	~Engine();
	bool init();
	bool update();
	void clean();
private:
	GraphicSystem m_graphicsSystem;
	Time m_time;
};

