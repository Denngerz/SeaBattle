#include "GameSession.h"
#include <memory>
#include "Game.h"

GameSession::GameSession(bool isFirstPlayerBot, bool isSecondPlayerBot, std::string chosenFirstPlayerName, std::string chosenSecondPlayerName, BotDifficulty chosenBotDifficulty, bool showFirstPlayer, bool showSecondPlayer)
    :isFirstPlayerBot(isFirstPlayerBot),
    isSecondPlayerBot(isSecondPlayerBot),
    chosenFirstPlayerName(chosenFirstPlayerName),
    chosenSecondPlayerName(chosenSecondPlayerName),
    chosenBotDifficulty(chosenBotDifficulty),
    showFirstPlayer(showFirstPlayer),
    showSecondPlayer(showSecondPlayer){}

void GameSession::runGameSession()
{
    initialize();
    
    while(!isGameSessionOver())
    {
        Game* singleGame = new Game(isFirstPlayerBot, isSecondPlayerBot, chosenFirstPlayerName, chosenSecondPlayerName, chosenBotDifficulty, showFirstPlayer, showSecondPlayer);

        singleGame->startRounds();

        distributePoints(singleGame->didfirstPlayerWin());
        currentRound++;

        delete singleGame;
    }
}

bool GameSession::isGameSessionOver()
{
    return firstPlayerWonRoundsAmmount >= winRoundsAmmount || secondPlayerWonRoundsAmmount >= winRoundsAmmount;
}

bool GameSession::didFirstPlayerWinGameSession()
{
    return firstPlayerWonRoundsAmmount == winRoundsAmmount;
}

void GameSession::distributePoints(bool firstPlayerWon)
{
    firstPlayerWon ? firstPlayerWonRoundsAmmount++ : secondPlayerWonRoundsAmmount++;
}

void GameSession::initialize()
{
    currentRound = 0;
    firstPlayerWonRoundsAmmount = 0;
    secondPlayerWonRoundsAmmount = 0;
}