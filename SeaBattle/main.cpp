#include "Game.h"
#include "main.h"


int main(int argc, char* argv[])
{
    StartGame();
    return 0;
}

void StartGame()
{
    Game game(1,2);
    game.startGame();
}