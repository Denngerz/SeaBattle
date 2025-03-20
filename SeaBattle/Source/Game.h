#pragma once

#include "../ThirdParty/nlohmann/json.hpp"
#include <memory>
#include "GameEnums.h"
#include "Field.h"

class SeaBattlePlayer;

class Field;

struct cell;

class Game
{
public:  
    Game(bool isFirstPlayerBot, bool isSecondPlayerBot, std::string chosenFirstPlayerName, std::string chosenSecondPlayerName, BotDifficulty chosenBotDifficulty, bool showFirstPlayer, bool showSecondPlayer);
        
    void startRounds();
    void logic();
    bool isRoundOver();
    void getInput();
    void generate();
    void initialize();

    void changeActivePlayer();
    void draw();
    bool didfirstPlayerWin();

    int fieldSize;

    int ammountOfMoves = 0;
    
private:
    //=====================Players, bots and their fields=====================//
    std::shared_ptr<SeaBattlePlayer> playerOne;
    std::shared_ptr<SeaBattlePlayer> playerTwo;

    Field* playerOneField;
    Field* playerTwoField;
    
    std::weak_ptr<SeaBattlePlayer> activePlayer;
    std::weak_ptr<SeaBattlePlayer> passivePlayer;
    
    void generatePlayers();
    void generatePlayersFields();

    std::string firstPlayerName;

    std::string secondPlayerName;
    
    BotDifficulty botDifficulty;

    //=====================Field=====================//
    int shootX, shootY;

    bool smbLostAllShips = false;

    bool areCoordinatesValid(int x, int y);

    //=====================Draw methods=====================//
    void drawWinner(SeaBattlePlayer* winner);

    void drawField();

    void drawCell(cell cell, bool isVisible);

    //=====================Game states=====================//
    bool activePlayerShootsAgain = false;

    bool wasShotValid = false;

    //=====================Rendering settings=====================//
    char waterSymbol = '.';

    char shipSymbol = '0';

    char destroyedShipSymbol = 'X';

    char destroyedWaterSymbol = '~';

    bool showFirstPlayerField;

    bool showSecondPlayerField;

    bool isFirstPlayerBot;

    bool isSecondPlayerBot;
};
