#pragma once

#include <memory>

class SeaBattlePlayer;

void startGame();

class Game
{
public:
    Game();
    
    void startRounds();
    void logic();
    bool isRoundOver();
    void getInput();
    void generate();

    void changeActivePlayer();
    void draw();
    
private:
    
    std::shared_ptr<SeaBattlePlayer> playerOne;
    std::shared_ptr<SeaBattlePlayer> playerTwo;
    std::weak_ptr<SeaBattlePlayer> activePlayer;
    std::weak_ptr<SeaBattlePlayer> passivePlayer;
    
    void generatePlayers();
    void generatePlayersFields();
    
    int shootX, shootY;

    bool smbLostAllShips = false;

    bool gameOver;

    bool areCoordinatesValid(int x, int y);
};
