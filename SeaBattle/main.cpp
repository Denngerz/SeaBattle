#include "Source/Game.h"
#include "Source/Lobby.h"

int main(int argc, char* argv[])
{
    Lobby* lobby = new Lobby();
    
    lobby->initialize();
    
    lobby->runGame();

    delete lobby;
    return 0;
}