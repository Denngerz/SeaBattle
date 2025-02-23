#include "Game.h"

#include <iostream>

#include "SeaBattlePlayer.h"

void startGame()
{
    
}

Game::Game()
{   
}

void Game::startRounds()
{
    while(!isRoundOver())
    {
        draw();
        getInput();
        logic();
    }
}

void Game::logic()
{
    passivePlayer->applyHitToField(shootX, shootY);

    if(!passivePlayer->field.isAnyShipsLeft())
    {
        smbLostAllShips = true;
    }

    if(!passivePlayer->field.smShipGotShot)
    {
        changeActivePlayer();
    }
}

bool Game::isRoundOver()
{
    return smbLostAllShips;
}

void Game::getInput()
{
    std::cin >> shootX;
    std::cin >> shootY;
}

void Game::changeActivePlayer()
{
    
}

void Game::draw()
{
    activePlayer->field.draw();
}

void Game::generatePlayers()
{
    playerOne = new SeaBattlePlayer(1);
    playerTwo = new SeaBattlePlayer(2);

    activePlayer = playerOne;
    passivePlayer = playerTwo;
}






