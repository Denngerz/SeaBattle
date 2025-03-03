#include "Game.h"
#include <iostream>
#include "SeaBattlePlayer.h"

const gameMode Game::pvp = {"PVP", 10, 10, '~', 'O', '*', 'X', false, false};
const gameMode Game::pve = {"PVE", 10, 10, '~', 'O', '*', 'X', true, false};
const gameMode Game::eve = {"EVE", 9, 9, '~', 'O', '*', 'X', true, true};

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
    chooseGameMode();
    generatePlayers();
    generatePlayersFields();
}

void Game::changeActivePlayer()
{
    std::swap(activePlayer, passivePlayer);
}


void Game::draw()
{
    drawField();
}

void Game::generatePlayers()
{
    playerOne = std::make_shared<SeaBattlePlayer>(1, currentMode.height, currentMode.width);
    playerTwo = std::make_shared<SeaBattlePlayer>(2, currentMode.height, currentMode.width);

    activePlayer = playerOne;
    passivePlayer = playerTwo;
}


void Game::generatePlayersFields()
{
    playerOne->generateBattleField();
    playerTwo->generateBattleField();
}

void Game::chooseGameMode()
{
    while(!gameModeSet)
    {
        setWantedGameMode(getWantedGameModeName());
    }
}

int Game::getWantedGameModeName()
{
    int gameMode;
    std::cout << "Enter the name of the game mode (1 - PVP, 2 - PVE, 3 - EVE): ";

    std::cin >> gameMode;
    while(std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> gameMode;
    }

    return gameMode;
}

void Game::setWantedGameMode(int wantedGameModeName)
{
    switch(wantedGameModeName)
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
    return passivePlayer.lock()->canHitAtFieldLocation(x, y);
}

void Game::drawField()
{
    int tempHeight = playerOne->getFieldHeight();
    int tempWidth = playerOne->getFieldWidth();
    
    for(int i = 0; i < tempHeight; i++)
    {
        if(currentMode.showFirstPlayerField)
        {
            std::vector<std::vector<cell>> field1 = playerOne->getFieldVector();
            
            for(auto cell: field1[i])
            {
                drawCell(cell);
                std::cout << " ";
            }
        }

        std::cout << "\t";

        if(currentMode.showSecondPlayerField)
        {
            std::vector<std::vector<cell>> field2 = playerTwo->getFieldVector();
            
            for(auto cell: field2[i])
            {
                drawCell(cell);
                std::cout << " ";
            }
        }

        std::cout << std::endl;
    }
}

void Game::drawCell(cell cell)
{
    if(cell.hasShip && !cell.wasShot)
    {
        std::cout << currentMode.shipSymbol;
    }
    else if(cell.hasShip && cell.wasShot)
    {
        std::cout << currentMode.destroyedShipSymbol;
    }
    else if(cell.wasShot && !cell.hasShip)
    {
        std::cout << currentMode.destroyedLocationSymbol;
    }
    else
    {
        std::cout << currentMode.waterSymbol;
    }
}

