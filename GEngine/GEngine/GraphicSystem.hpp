#pragma once

#include "GraphicsSystem.h"

using namespace Demo;

class GraphicSystem final : public GraphicsSystem 
{
    void setupResources() override {}

public:
    GraphicSystem() {}
    GraphicSystem(GameState* gameState) : GraphicsSystem(gameState) {}
};