#include "Game/Game.h"
#include "Globals.h"

int main(int argc, char *argv[])
{
    Game game;

    game.Initialize();
    game.Run();
    game.Destroy();

    return 0;
}
