#pragma once
#include "../Game.h"

namespace GEngine 
{
    namespace Descent 
    {
        class DescentGame : public Game
        {
        public:
            void createScene01() override;
            void update(float dt) override;
            void keyPressed(const SDL_KeyboardEvent& arg) override;
            void keyReleased(const SDL_KeyboardEvent& arg) override;

        };
    }
}