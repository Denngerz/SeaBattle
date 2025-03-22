#include "Lobby.h"
#include <iostream>
#include <fstream>

#include "GameSession.h"
#include "StatsPlayer.h"
#include "MMRService.h"

Lobby::Lobby()
{
    playerOne = std::make_shared<Player>();
    playerTwo = std::make_shared<Player>();
}

void Lobby::initialize()
{
    chooseGamemode();

    initializePlayers();

    if(playerOne->isBot || playerTwo->isBot)
    {
        chooseBotDifficulty();
    }
}

void Lobby::runGame()
{
    GameSession* gameSession = createGameSession();

    gameSession->runGameSession();

    updatePlayersStats(gameSession->didFirstPlayerWinGameSession());
}

//=====================Player Initizalization=====================//
void Lobby::initializePlayers()
{
    botAmmount = 0;
    initializePlayer(playersJson, playerOne.get());
    initializePlayer(playersJson, playerTwo.get());
}

void Lobby::initializePlayer(const std::string playersJson, Player* player)
{
    if(!player->isBot)
    {
        drawNameChoose();
    
        player->name = choosePlayerName();
    }
    else
    {
        botAmmount++;
        player->name = "Bot" + std::to_string(botAmmount);
    }
    
    player->statsPlayer = std::make_shared<StatsPlayer>(player->name, playersJson);
    player->statsPlayer->setStatsPlayer();
}

std::string Lobby::choosePlayerName()
{
    std::string playerName;

    std::cin >> playerName;

    return playerName;
}

//=====================Draw methods=====================//
void Lobby::drawNameChoose()
{
    std::cout << "\nChoose Player Name: ";
}

void Lobby::drawGamemodeChoose()
{
    std::cout << "\nChoose Gamemode (1 - PVP, 2 - PVE, 3 - EVE): ";
}

void Lobby::drawDifficultyChoose()
{
    std::cout << "\nChoose Bot Difficulty (1 - EASY, 2 - NORMAL, 3 - HARD): ";
}

//=====================Gamemode=====================//
void Lobby::chooseGamemode()
{
    while(!gamemodeSet)
    {
        drawGamemodeChoose();
        
        int wantedGamemode = getWantedGamemode();
        
        setWantedGamemode(wantedGamemode);
    }
}

void Lobby::setWantedGamemode(int wantedGamemode)
{
    switch(wantedGamemode)
    {
        case 1:
            playerOne->isBot = false;
            playerTwo->isBot = false;
            gamemodeSet = true;
            break;
        
        case 2:
            playerOne->isBot = false;
            playerTwo->isBot = true;
            gamemodeSet = true;
            break;
        
        case 3:
            playerOne->isBot = true;
            playerTwo->isBot = true;
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

//=====================Bot Difficulty=====================//
void Lobby::chooseBotDifficulty()
{
    while(!botDifficultySet)
    {
        drawDifficultyChoose();
        
        int wantedBotDifficulty = getWantedBotDifficulty();
        
        setWantedBotDifficulty(wantedBotDifficulty);
    }
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

//=====================Player Stats update function=====================//
void Lobby::updatePlayersStats(bool firstPlayerWon)
{
    MMRService::updatePlayer(playerOne->statsPlayer.get(), playerTwo->statsPlayer.get(), firstPlayerWon);
}

//=====================Create Game function=====================//
GameSession* Lobby::createGameSession()
{
    bool showFirstPlayerField = playerOne->isBot || playerTwo->isBot;
    bool showSecondPlayerField = playerOne->isBot;

    return new GameSession(
        playerOne->isBot, 
        playerTwo->isBot, 
        playerOne->name, 
        playerTwo->name, 
        chosenBotDifficulty, 
        showFirstPlayerField, 
        showSecondPlayerField
    );
}