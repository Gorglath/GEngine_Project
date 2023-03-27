#pragma once
#include "Game.h"
#include "SlidingSphere.h"
namespace GEngine
{
    namespace SlidingSphere
    {
        class SlidingSphereGame :
            public Game
        {
        public:
            void createScene01() override;
            void update(float dt) override;
            void keyPressed(const SDL_KeyboardEvent& arg) override;
            void keyReleased(const SDL_KeyboardEvent& arg) override;
        private:
            SlidingSphere m_sphere;
            InputData m_inputData;
        };
    }
}
