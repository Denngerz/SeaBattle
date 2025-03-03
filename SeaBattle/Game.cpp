#include "Game.h"
#include <iostream>
#include "SeaBattlePlayer.h"

void startGame()
{
    Game game;
}

Game::Game()
{
    startRounds();
}

void Game::startRounds()
{
    generate();
    
    while(!isRoundOver())
    {
        draw();
        getInput();
        logic();
    }
}

void Game::logic()
{
    if(areCoordinatesValid(shootX, shootY))
    {
        passivePlayer.lock()->applyHitToField(shootX, shootY);
    }

    if(!passivePlayer.lock()->isAnyShipsLeftOnField())
    {
        smbLostAllShips = true;
    }

    if(!passivePlayer.lock()->isAnyShipGotShot())
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
    
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    
    std::cin >> shootY;
    
    if(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    shootX --;
    shootY --;
}

void Game::generate()
{
    generatePlayers();
    generatePlayersFields();
}

void Game::changeActivePlayer()
{
    std::swap(activePlayer, passivePlayer);
}


void Game::draw()
{
    activePlayer.lock()->drawField();
}

void Game::generatePlayers()
{
    playerOne = std::make_shared<SeaBattlePlayer>(1);
    playerTwo = std::make_shared<SeaBattlePlayer>(2);

    activePlayer = playerOne;
    passivePlayer = playerTwo;
}


void Game::generatePlayersFields()
{
    playerOne->generateBattleField();
    playerTwo->generateBattleField();
}

bool Game::areCoordinatesValid(int x, int y)
{
    return passivePlayer.lock()->canHitAtFieldLocation(x, y);
}

