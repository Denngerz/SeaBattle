#pragma once

#include <memory>
#include <string>

class SeaBattlePlayer;

void startGame();

struct cell;

struct gameMode
{
    std::string name;
    
    //Field
    int width, height;
    char waterSymbol, shipSymbol, destroyedLocationSymbol, destroyedShipSymbol;

    //Draw
    bool showFirstPlayerField, showSecondPlayerField;
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

    void changeActivePlayer();
    void draw();

    void chooseGameMode();

    int getWantedGameModeName();

    void setWantedGameMode(int wantedGameModeName);
    
private:
    
    std::shared_ptr<SeaBattlePlayer> playerOne;
    std::shared_ptr<SeaBattlePlayer> playerTwo;
    std::weak_ptr<SeaBattlePlayer> activePlayer;
    std::weak_ptr<SeaBattlePlayer> passivePlayer;

    gameMode currentMode; 
    
    static const gameMode pvp;
    static const gameMode pve;
    static const gameMode eve;
    
    void generatePlayers();
    void generatePlayersFields();
    
    int shootX, shootY;

    bool smbLostAllShips = false;

    bool gameOver;

    bool areCoordinatesValid(int x, int y);

    bool gameModeSet = false;

    void drawField();

    void drawCell(cell cell);
};
