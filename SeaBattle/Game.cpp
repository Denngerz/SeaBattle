#include "Game.h"
#include <iostream>
#include "SeaBattlePlayer.h"

void startGame()
{
    Game game;
    game.startRounds();
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
    shootX --;
    shootY --;
    
    if(areCoordinatesValid(shootX, shootY))
    {
        passivePlayer->applyHitToField(shootX, shootY);
    }

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
    activePlayer->drawField();
}

void Game::generatePlayers()
{
    playerOne = std::make_unique<SeaBattlePlayer>(1);
    playerTwo = std::make_unique<SeaBattlePlayer>(2);

    activePlayer = playerOne.get();
    passivePlayer = playerTwo.get();
}


void Game::generatePlayersFields()
{
    playerOne->generateBattleField();
    playerTwo->generateBattleField();
}

bool Game::areCoordinatesValid(int x, int y)
{
    return passivePlayer->field.canShootAtLocation(x, y);
}

