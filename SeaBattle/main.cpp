#include "Game.h"
#include "Lobby.h"

int main(int argc, char* argv[])
{
    Lobby* lobby = new Lobby();
    
    lobby->initialize();
    
    lobby->runGame();

    delete lobby;
    return 0;
}