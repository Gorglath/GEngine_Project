#include "Engine.h"
int main(int argc, char *argv[])
{
    Engine engine;

    engine.init();
    bool quit = false;
    while (!engine.update())
    {

    }
}
