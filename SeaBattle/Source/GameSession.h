#pragma once
#include <string>

#include "GameEnums.h"

class GameSession
{
public:
    GameSession(bool isFirstPlayerBot, bool isSecondPlayerBot, std::string chosenFirstPlayerName, std::string chosenSecondPlayerName, BotDifficulty chosenBotDifficulty, bool showFirstPlayer, bool showSecondPlayer);

    //====Game params====//
    bool isFirstPlayerBot;
    
    bool isSecondPlayerBot;
    
    std::string chosenFirstPlayerName;
    
    std::string chosenSecondPlayerName;
    
    BotDifficulty chosenBotDifficulty;
    
    bool showFirstPlayer;
    
    bool showSecondPlayer;

    //====Game session
    void runGameSession();
    
    void initialize();
    
    bool isGameSessionOver();

    int currentRound;

    bool didFirstPlayerWinGameSession();

private:
    //====Game session params====//
    int winRoundsAmmount = 3;

    int firstPlayerWonRoundsAmmount;

    int secondPlayerWonRoundsAmmount;
    
    void distributePoints(bool firstPlayerWon);
};