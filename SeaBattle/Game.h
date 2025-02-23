#pragma once

#include <memory>

class SeaBattlePlayer;
class Game;

void startGame();

class Game
{

public:
    void startRounds();
    void logic();
    bool isRoundOver();
    void getInput();
    void generate();

    void changeActivePlayer();
    void draw();
    
private:
    
    std::unique_ptr<SeaBattlePlayer> playerOne;
    std::unique_ptr<SeaBattlePlayer> playerTwo;
    SeaBattlePlayer* activePlayer;
    SeaBattlePlayer* passivePlayer;
    
    void generatePlayers();
    void generatePlayersFields();
    
    int shootX, shootY;

    bool smbLostAllShips = false;

    bool gameOver;

    bool areCoordinatesValid(int x, int y);
};
