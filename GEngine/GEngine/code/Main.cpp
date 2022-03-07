#include "engine/Engine.h"
#include "game/SlidingSphereGame.h"

int main(int argc, char *argv[])
{
    Game game;
    Engine engine;

    engine.init(game);

    //game.init(&engine.m_graphicsSystem);
    
    engine.loadScene();

    bool quit = false;
    while (!engine.update())
    {
        //game.update(Time::getDeltaTime());
    }
}
