#pragma once
#include "Game.h"
#include "SlidingSphere.h"
    class SlidingSphereGame :
        public Game
    {
    public:
        void createScene01() override;
        void update(float dt) override;
    private:
        SlidingSphere m_sphere;
    };

