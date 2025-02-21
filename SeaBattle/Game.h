#pragma once
#include "SeaBattlePlayer.h"

class Game;

void startGame(Game& game);

class Game
{
private:
    SeaBattlePlayer playerOne;
    SeaBattlePlayer playerTwo;
    SeaBattlePlayer* activePlayer;
    
    void generatePlayers();
    
    int shootX, shootY;

public:
    Game(unsigned int seed1, unsigned int seed2);
    
    void startRounds();

    void changeActivePlayer();
    void drawActivePlayer();
    void getInput();

    void logic();
    bool isRoundOver();
    
    SeaBattlePlayer* getPassivePlayer();
};
