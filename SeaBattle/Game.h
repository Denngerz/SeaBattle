#pragma once

#include <memory>

class SeaBattlePlayer;

class Field;

struct cell;

void startGame();

enum GamemodeNames
{
    PVP,
    PVE,
    EVE
};

struct gameMode
{
    GamemodeNames name;
};

class Game
{
public:
    Game();
    
    void startRounds();
    void logic();
    bool isRoundOver();
    void getInput();
    void generate();
    void initialize();

    void changeActivePlayer();
    void draw();

    void chooseGameMode();

    int getWantedGameModeName();

    void setWantedGameMode(int wantedGameModeName);
    
private:
    
    std::shared_ptr<SeaBattlePlayer> playerOne;
    std::shared_ptr<SeaBattlePlayer> playerTwo;

    Field* playerOneField;
    Field* playerTwoField;

    Field* passivePlayerField;
    Field* activePlayerField;
    
    std::weak_ptr<SeaBattlePlayer> activePlayer;
    std::weak_ptr<SeaBattlePlayer> passivePlayer;

    gameMode currentMode; 
    
    static const gameMode pvp;
    static const gameMode pve;
    static const gameMode eve;
    
    void generatePlayers();
    void generatePlayersFields();
    void changeActiveField();
    
    int shootX, shootY;

    bool smbLostAllShips = false;

    bool areCoordinatesValid(int x, int y);
    
    bool gameModeSet = false;

    void drawField();

    void drawCell(cell cell, bool isVisible);

    bool activePlayerShootsAgain = false;

    bool wasShotValid = false;

    char waterSymbol = '.';

    char shipSymbol = '0';

    char destroyedShipSymbol = 'X';

    char destroyedWaterSymbol = '~';

    bool showFirstPlayerField;

    bool showSecondPlayerField;

};
