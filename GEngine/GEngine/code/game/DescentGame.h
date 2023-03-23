#pragma once
#include "Game.h"

class DescentGame : public Game
{
public:
    void createScene01() override;
    void update(float dt) override;
    void keyPressed(const SDL_KeyboardEvent& arg) override;
    void keyReleased(const SDL_KeyboardEvent& arg) override;

};