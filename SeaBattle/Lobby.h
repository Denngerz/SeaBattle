#pragma once

#include <memory>
#include <string>
#include "GameEnums.h"

class SeaBattlePlayer;
class StatsPlayer;

class Lobby
{
public:
    GameMode chosenGamemode;
    
    BotDifficulty chosenBotDifficulty;

    std::string firstPlayerName;

    std::string secondPlayerName;

    void initialize();

    void chooseGamemode();

    void initializePlayers();

    void chooseBotDifficulty();

    std::string choosePlayerName();

    void draw();

    void runGame();

private:
    const std::string playersJson = "players.json";

    bool gamemodeSet = false;

    bool firstPlayerNameSet = false;

    bool secondPlayerNameSet = false;

    void setWantedGamemode(int wantedGamemode);

    int getWantedGamemode();

    void setWantedBotDifficulty(int wantedBotDifficulty);

    int getWantedBotDifficulty();

    bool botDifficultySet = true;

    std::shared_ptr<StatsPlayer> firstStatsPlayer;

    std::shared_ptr<StatsPlayer> secondStatsPlayer;

    void updatePlayersStats(SeaBattlePlayer* winner, SeaBattlePlayer* loser, int ammountOfMoves, int fieldSize);

    int defaultMMRBonus = 20;
};
