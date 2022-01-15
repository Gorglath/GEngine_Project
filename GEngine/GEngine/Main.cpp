#include "Engine.h"
int main(int argc, const char* argv[])
{
    Engine engine;

    engine.init();
    bool quit = false;
    while (!quit)
    {
        quit = engine.getWindowQuit();
        if (!quit)
            quit = !engine.update();
    }
}
