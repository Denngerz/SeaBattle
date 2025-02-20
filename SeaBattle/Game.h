#pragma once
#include "SeaBattlePlayer.h"

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
    
    void startGame();

    void changeActivePlayer();
    void drawActivePlayer();
    void getInput();

    void logic();
    bool isRoundOver();
    
    SeaBattlePlayer* getPassivePlayer();
};
