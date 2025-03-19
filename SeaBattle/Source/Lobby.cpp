#include "Lobby.h"
#include <iostream>
#include "Game.h"
#include <fstream>

#include "SeaBattleBot.h"
#include "SeaBattlePlayer.h"
#include "StatsPlayer.h"

void Lobby::initialize()
{
    chooseGamemode();

    initializePlayers();

    if(chosenGamemode != GameMode::PVP)
    {
        botDifficultySet = false;
        chooseBotDifficulty();
    }
}

void Lobby::chooseGamemode()
{
    while(!gamemodeSet)
    {
        draw();
        
        int wantedGamemode = getWantedGamemode();
        
        setWantedGamemode(wantedGamemode);
    }
}

void Lobby::initializePlayers()
{
    if(chosenGamemode == GameMode::PVP)
    {
        draw();
        
        firstPlayerName = choosePlayerName();

        firstStatsPlayer = std::make_shared<StatsPlayer>(firstPlayerName, playersJson);
        firstStatsPlayer->setStatsPlayer();
        firstPlayerNameSet = true;
        
        draw();
        
        secondPlayerName = choosePlayerName();

        secondStatsPlayer = std::make_shared<StatsPlayer>(secondPlayerName, playersJson);
        secondStatsPlayer->setStatsPlayer();
        secondPlayerNameSet = true;
        
        return;
    }
    if(chosenGamemode == GameMode::PVE)
    {
        draw();
        
        firstPlayerName = choosePlayerName();
        
        firstStatsPlayer = std::make_shared<StatsPlayer>(firstPlayerName, playersJson);
        firstStatsPlayer->setStatsPlayer();
        firstPlayerNameSet = true;
        
        secondPlayerName = "Bot1";
        secondPlayerNameSet = true;
        
        return;
    }
    if(chosenGamemode == GameMode::EVE)
    {
        firstPlayerName = "Bot1";
        firstPlayerNameSet = true;

        secondPlayerName = "Bot2";
        secondPlayerNameSet = true;
    }
}

void Lobby::chooseBotDifficulty()
{
    while(!botDifficultySet)
    {
        draw();
        
        int wantedBotDifficulty = getWantedBotDifficulty();
        
        setWantedBotDifficulty(wantedBotDifficulty);
    }
}

std::string Lobby::choosePlayerName()
{
    std::string playerName;

    std::cin >> playerName;

    return playerName;
}

void Lobby::draw()
{
    if(!gamemodeSet)
    {
        std::cout << "\nChoose Gamemode (1 - PVP, 2 - PVE, 3 - EVE): ";
        return;
    }
    if(!firstPlayerNameSet)
    {
        std::cout << "\nChoose First Player Name: ";
        return;
    }
    if(!secondPlayerNameSet)
    {
        std::cout << "\nChoose Second Player Name: ";
    }
    if(!botDifficultySet)
    {
        std::cout << "\nChoose Bot Difficulty (1 - EASY, 2 - NORMAL, 3 - HARD): ";
    }
}

void Lobby::runGame()
{
    Game* game = new Game(chosenGamemode, firstPlayerName, secondPlayerName, chosenBotDifficulty);

    game->startRounds();

    updatePlayersStats(game->getWinner(), game->getLoser(), game->ammountOfMoves, game->fieldSize);
}

void Lobby::setWantedGamemode(int wantedGamemode)
{
    switch(wantedGamemode)
    {
        case 1:
            chosenGamemode = GameMode::PVP;
            gamemodeSet = true;
            break;
        
        case 2:
            chosenGamemode = GameMode::PVE;
            gamemodeSet = true;
            break;
        
        case 3:
            chosenGamemode = GameMode::EVE;
            gamemodeSet = true;
            break;
        
        default:
            gamemodeSet = false;
            break;
    }
}

int Lobby::getWantedGamemode()
{
    int wantedGamemode;

    std::cin >> wantedGamemode;
    
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return wantedGamemode;
}

void Lobby::setWantedBotDifficulty(int wantedBotDifficulty)
{
    switch(wantedBotDifficulty)
    {
    case 1:
        chosenBotDifficulty = BotDifficulty::EASY;
        botDifficultySet = true;
        break;
        
    case 2:
        chosenBotDifficulty = BotDifficulty::NORMAL;
        botDifficultySet = true;
        break;
        
    case 3:
        chosenBotDifficulty = BotDifficulty::HARD;
        botDifficultySet = true;
        break;
        
    default:
        botDifficultySet = false;
        break;
    }
}

int Lobby::getWantedBotDifficulty()
{
    int wantedBotDifficulty;

    std::cin >> wantedBotDifficulty;
    
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return wantedBotDifficulty;
}

void Lobby::updatePlayersStats(SeaBattlePlayer* winner, SeaBattlePlayer* loser, int ammountOfMoves, int fieldSize)
{
    bool isWinnerBot = dynamic_cast<SeaBattleBot*>(winner) != nullptr;
    bool isLoserBot = dynamic_cast<SeaBattleBot*>(loser) != nullptr;

    if (!isWinnerBot && winner->username == firstStatsPlayer->username)
    {
        firstStatsPlayer->updatePlayerStats(true, ammountOfMoves, defaultMMRBonus, fieldSize);
    }
    if (!isWinnerBot && winner->username == secondStatsPlayer->username)
    {
        secondStatsPlayer->updatePlayerStats(true, ammountOfMoves, defaultMMRBonus, fieldSize);
    }

    if (!isLoserBot && loser->username == firstStatsPlayer->username)
    {
        firstStatsPlayer->updatePlayerStats(false, ammountOfMoves, defaultMMRBonus, fieldSize);
    }
    if (!isLoserBot && loser->username == secondStatsPlayer->username)
    {
        secondStatsPlayer->updatePlayerStats(false, ammountOfMoves, defaultMMRBonus, fieldSize);
    }
}