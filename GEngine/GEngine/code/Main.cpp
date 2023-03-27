#include "engine/Engine.h"
#include "game/SlidingSphereGame.h"
#include "engine/JsonParser.h"
using namespace GEngine;
int main(int argc, char *argv[])
{
    GEngine::SlidingSphere::SlidingSphereGame game;
    Engine engine;

    engine.init(game);

    game.init(&engine.m_graphicsSystem);
    
    engine.loadScene();

    bool quit = false;
    JsonToLevelParser::GetGameEntitiesFromLevelJson("level1.json");
    while (!engine.update())
    {
        game.update(Time::getDeltaTime());
    }
}
