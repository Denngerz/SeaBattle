#pragma once
#include "SeaBattlePlayer.h"

class Game;

void startGame();

class Game
{

public:
    Game();
    
    void startRounds();
    void logic();
    bool isRoundOver();
    void getInput();

    void changeActivePlayer();
    void draw();
    
private:
    SeaBattlePlayer *playerOne;
    SeaBattlePlayer *playerTwo;
    SeaBattlePlayer *activePlayer;
    SeaBattlePlayer *passivePlayer;
    
    void generatePlayers();
    
    int shootX, shootY;

    bool smbLostAllShips = false;

    bool gameOver;
};
