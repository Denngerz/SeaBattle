#include "Game.h"
#include <iostream>
#include "SeaBattlePlayer.h"

Game::Game(unsigned int seed1, unsigned int seed2): playerOne(seed1), playerTwo(seed2)
{
    generatePlayers();
    activePlayer = &playerOne;
}

void Game::startRounds()
{
    while(!isRoundOver())
    {
        drawActivePlayer();
        getInput();
        logic();
        changeActivePlayer();
    }
}

void startGame(Game& game)
{
    game.startRounds();
}

void Game::generatePlayers()
{
    playerOne.generate();
    playerTwo.generate();
}

void Game::changeActivePlayer()
{
    activePlayer = (activePlayer == &playerOne) ? &playerTwo : &playerOne;
}

void Game::drawActivePlayer()
{
    activePlayer->draw();
}

void Game::getInput()
{
    std::cin >> shootX;
    std::cin >> shootY;
}

void Game::logic()
{
    getPassivePlayer()->implementHitAtLocation(shootX,shootY);
}

bool Game::isRoundOver()
{
    return activePlayer->isAnyShipsLeft();
}

SeaBattlePlayer* Game::getPassivePlayer()
{
    return (activePlayer == &playerOne) ? &playerTwo : &playerOne;
}






