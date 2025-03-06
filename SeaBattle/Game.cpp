#include "Game.h"
#include <iostream>
#include "Field.h"
#include "SeaBattleBot.h"
#include "SeaBattlePlayer.h"

const gameMode Game::pvp = {gamemodeNames::PVP};
const gameMode Game::pve = {gamemodeNames::PVE};
const gameMode Game::eve = {gamemodeNames::EVE};

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
    initialize();
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
        wasShotValid = true;
    }
    else
    {
        wasShotValid = false;
    }
    
    if(!passivePlayer.lock()->isAnyShipsLeftOnField())
    {
        smbLostAllShips = true;
        drawField();
    }

    if(!passivePlayer.lock()->isAnyShipGotShot() && wasShotValid)
    {
        activePlayerShootsAgain = false;
        changeActivePlayer();
    }
    else
    {
        activePlayerShootsAgain = true;
    }
}

bool Game::isRoundOver()
{
    return smbLostAllShips;
}

void Game::getInput()
{
    if(auto botPlayer = std::dynamic_pointer_cast<SeaBattleBot>(activePlayer.lock()))
    {
        botPlayer->generateShootLocations();
        shootX = botPlayer->getShootX();
        shootY = botPlayer->getShootY();
    }
    else
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
    
    shootX --;
    shootY --;
}

void Game::generate()
{
    generatePlayers();
    generatePlayersFields();
}

void Game::initialize()
{
    chooseGameMode();

    if(currentMode.name == gamemodeNames::PVP)
    {
        waterSymbol = '.';

        shipSymbol = '0';

        destroyedShipSymbol = 'X';

        destroyedWaterSymbol = '~';

        showFirstPlayerField = false; 

        showSecondPlayerField = false; 
    }

    if(currentMode.name == gamemodeNames::PVE)
    {
        waterSymbol = '.';

        shipSymbol = '0';

        destroyedShipSymbol = 'X';

        destroyedWaterSymbol = '~';

        showFirstPlayerField = true; 

        showSecondPlayerField = false; 
    }

    if(currentMode.name == gamemodeNames::EVE)
    {
        waterSymbol = '.';

        shipSymbol = '0';

        destroyedShipSymbol = 'X';

        destroyedWaterSymbol = '~';

        showFirstPlayerField = true; 

        showSecondPlayerField = true; 
    }
}

void Game::changeActivePlayer()
{
    std::swap(activePlayer, passivePlayer);
}

void Game::draw()
{
    if (gameModeSet)
    {
        auto bot = std::dynamic_pointer_cast<SeaBattleBot>(activePlayer.lock());
        if(true)
        {
            std::cout << std::endl;

            if(wasShotValid && activePlayerShootsAgain)
            {
                drawField();
                std::cout << "Shoot again: ";
            }
            else if(!wasShotValid && activePlayerShootsAgain)
            {
                std::cout << "Enter valid shoot location: ";
            }
            else
            {
                drawField();
                std::cout << "Player's " << activePlayer.lock()->id << " turn"<< std::endl;
                std::cout << "Enter shoot location (x, y): ";
            }
        }
    }
    else
    {
        std::cout << "Enter the name of the game mode (1 - PVP, 2 - PVE, 3 - EVE): ";
    }
}

void Game::generatePlayers()
{
    if(gameModeSet)
    {
        if(currentMode.name == pvp.name)
        {
            playerOne = std::make_shared<SeaBattlePlayer>(1, 10, 10, 1);
            playerTwo = std::make_shared<SeaBattlePlayer>(2, 10, 10, 2);
        }
        
        if(currentMode.name == pve.name)
        {
            playerOne = std::make_shared<SeaBattlePlayer>(1, 10, 10, 1);
            playerTwo = std::make_shared<SeaBattleBot>(2, 10, 10, 2);
        }
        
        if(currentMode.name == eve.name)
        {
            playerOne = std::make_shared<SeaBattleBot>(1, 10, 10, 1);
            playerTwo = std::make_shared<SeaBattleBot>(2, 10, 10, 2);
        }

        activePlayer = playerOne;
        passivePlayer = playerTwo;
    }
}

void Game::generatePlayersFields()
{
    playerOne->generateBattleField();

    playerOneField = playerOne->field.get();
    
    playerTwo->generateBattleField();

    playerTwoField = playerTwo->field.get();
}

void Game::chooseGameMode()
{
    while(!gameModeSet)
    {
        draw();
        setWantedGameMode(getWantedGameModeName());
    }
}

int Game::getWantedGameModeName()
{
    int gameMode;
    std::cin >> gameMode;
    
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return gameMode;
}

void Game::setWantedGameMode(int wantedGameMode)
{
    switch(wantedGameMode)
    {
        case 1:
            currentMode = pvp;
            gameModeSet = true;
            break;
        
        case 2:
            currentMode = pve;
            gameModeSet = true;
            break;
        
        case 3:
            currentMode = eve;
            gameModeSet = true;
            break;
        default:
            gameModeSet = false;
    }
}

bool Game::areCoordinatesValid(int x, int y)
{
    return passivePlayer.lock() ->canHitAtFieldLocation(x, y);
}

void Game::drawField()
{
    int tempHeight = playerOne->getFieldHeight();
    int tempWidth = playerOne->getFieldWidth();

    std::cout << std::endl;
    
    std::cout<< "   ";
    for (int i = 0; i < tempWidth; i++)
    {
        std::cout << i + 1 << " ";
    }
    
    std::cout<< "     ";
    for (int i = 0; i < tempWidth; i++)
    {
        std::cout << i + 1 << " ";
    }

    std::cout << std::endl;
    
    for(int i = 0; i < tempHeight; i++)
    {
        if(i + 1 < 10)
        {
            std::cout << i + 1 << "  ";
        }
        else
        {
            std::cout << i + 1 << " ";
        }   
            
        for(int j = 0; j < tempWidth; j++)
        {
            drawCell(playerOneField->getCellAt(j, i), showFirstPlayerField);
            std::cout << " ";
        }

        std::cout << "   ";

        if(i+1 < 10)
        {
            std::cout << i + 1 << "  ";
        }
        else
        {
            std::cout << i + 1 << " ";
        }
            
        for(int j = 0; j < tempWidth; j++)
        {
            drawCell(playerTwoField->getCellAt(j, i), showSecondPlayerField);
            if(i >= 10)
            {
                std::cout << "  ";
            }
            else
            {
                std::cout << " ";
            }
        }
        
        std::cout << std::endl;
    }
}

void Game::drawCell(cell cell, bool isVisible)
{
    if(isVisible)
    {
        if(!cell.hasShip && !cell.wasShot)
        {
            std::cout << waterSymbol;
        }
        if(cell.hasShip&& !cell.wasShot)
        {
            std::cout << shipSymbol;
        }
        if(!cell.hasShip&& cell.wasShot)
        {
            std::cout << destroyedWaterSymbol;
        }
        if(cell.hasShip&& cell.wasShot)
        {
            std::cout << destroyedShipSymbol;
        }
    }
    else
    {
        if(cell.hasShip && cell.wasShot)
        {
            std::cout << destroyedShipSymbol;
        }
        if(!cell.hasShip&& cell.wasShot)
        {
            std::cout << destroyedWaterSymbol;
        }
        else
        {
            std::cout << waterSymbol;
        }
    }
}

