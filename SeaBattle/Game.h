#pragma once

#include "ThirdParty/nlohmann/json.hpp"
#include <memory>
#include "GameEnums.h"
#include "Field.h"

class SeaBattlePlayer;

class Field;

struct cell;

class Game
{
public:
    Game(GameMode chosenGamemode, std::string chosenFirstPlayerName, std::string chosenSecondPlayerName, BotDifficulty chosenBotDifficulty);
        
    void startRounds();
    void logic();
    bool isRoundOver();
    void getInput();
    void generate();
    void initialize();

    void changeActivePlayer();
    void draw();

    int fieldSize;

    SeaBattlePlayer* getWinner();

    SeaBattlePlayer* getLoser();

    int ammountOfMoves = 0;
    
private:
    
    std::shared_ptr<SeaBattlePlayer> playerOne;
    std::shared_ptr<SeaBattlePlayer> playerTwo;

    Field* playerOneField;
    Field* playerTwoField;
    
    std::weak_ptr<SeaBattlePlayer> activePlayer;
    std::weak_ptr<SeaBattlePlayer> passivePlayer;
    
    void generatePlayers();
    void generatePlayersFields();
    
    int shootX, shootY;

    bool smbLostAllShips = false;

    bool areCoordinatesValid(int x, int y);

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

    GameMode gamemode;

    std::string firstPlayerName;

    std::string secondPlayerName;

    BotDifficulty botDifficulty;
};
