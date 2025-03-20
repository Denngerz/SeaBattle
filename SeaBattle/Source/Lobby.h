#pragma once

#include <memory>
#include <string>
#include "GameEnums.h"

class StatsPlayer;
class Game;

struct Player
{
    bool isBot;
    std::shared_ptr<StatsPlayer> statsPlayer;
    std::string name;
};

class Lobby
{
public:
    Lobby();

    void initialize();

    void chooseGamemode();

    void initializePlayers();

    void chooseBotDifficulty();

    std::string choosePlayerName();

    void runGame();

private:
    //=====Players in lobby=====//
    std::shared_ptr<Player> playerOne;

    std::shared_ptr<Player> playerTwo;

    void initializePlayer(const std::string playersJson, Player* player);

    void updatePlayersStats(bool firstPlayerWon, int ammountOfMoves, int fieldSize);
    
    //=====Draw Methods=====//
    void drawNameChoose();

    void drawGamemodeChoose();

    void drawDifficultyChoose();

    //=====Players stats File=====//
    const std::string playersJson = "players.json";

    //=====Gamemode=====//
    bool gamemodeSet = false;

    void setWantedGamemode(int wantedGamemode);

    int getWantedGamemode();

    //=====Bot Difficulty=====//
    BotDifficulty chosenBotDifficulty;

    void setWantedBotDifficulty(int wantedBotDifficulty);

    int getWantedBotDifficulty();

    bool botDifficultySet = false;

    //====Other====//
    int defaultMMRBonus = 20;
    
    Game* createGame();
};
