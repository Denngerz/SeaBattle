#pragma once

#include <memory>
#include <string>
#include <nlohmann/json.hpp>

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

    int ammountOfMoves = 0;
    
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

    nlohmann::json playersDB;

    int defaultMMRBonus = 20;
    
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

    void drawWinner(SeaBattlePlayer* winner);

    bool activePlayerShootsAgain = false;

    bool wasShotValid = false;

    char waterSymbol = '.';

    char shipSymbol = '0';

    char destroyedShipSymbol = 'X';

    char destroyedWaterSymbol = '~';

    bool showFirstPlayerField;

    bool showSecondPlayerField;

    const std::string playerDBPath = "playersDB.json";

    bool firstPlayerCreated = false;
    
    bool secondPlayerCreated = false;

    void setPlayers();

    void createNewProfile(std::string username);

    void savePlayersDB();

    void updatePlayersStats(SeaBattlePlayer* winner, SeaBattlePlayer* loser, int ammountOfMoves);

    void updatePlayerStatsInFile(SeaBattlePlayer* currentPlayer);
};
