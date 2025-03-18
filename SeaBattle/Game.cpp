#include "Game.h"
#include <iostream>
#include <iomanip>
#include "Field.h"
#include "SeaBattleBot.h"
#include "SeaBattlePlayer.h"

Game::Game(GameMode chosenGamemode, std::string chosenFirstPlayerName, std::string chosenSecondPlayerName, BotDifficulty chosenBotDifficulty)
{
    gamemode = chosenGamemode;
    firstPlayerName = chosenFirstPlayerName;
    secondPlayerName = chosenSecondPlayerName;
    botDifficulty = chosenBotDifficulty;
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
    if(auto bot = std::dynamic_pointer_cast<SeaBattleBot>(activePlayer.lock()))
    {
        bot->generateShootLocations();
        
        shootX = bot->getShootX();
        shootY = bot->getShootY();
    }
    
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
        
        drawWinner(activePlayer.lock().get());
        
        return;
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

    ammountOfMoves++;
}

bool Game::isRoundOver()
{
    return smbLostAllShips;
}

void Game::getInput()
{
    if(!std::dynamic_pointer_cast<SeaBattleBot>(activePlayer.lock()))
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
}

void Game::generate()
{
    generatePlayers();
    generatePlayersFields();
}

void Game::initialize()
{
    if(gamemode == GameMode::PVP)
    {
        showFirstPlayerField = false; 

        showSecondPlayerField = false; 
    }

    if(gamemode == GameMode::PVE)
    {
        showFirstPlayerField = true; 

        showSecondPlayerField = false; 
    }

    if(gamemode == GameMode::EVE)
    {
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
        std::cout << "Player's " << activePlayer.lock()->username << " turn"<< std::endl;
        std::cout << "Enter shoot location (x, y): ";
    }
}

SeaBattlePlayer* Game::getWinner()
{
    return activePlayer.lock().get();
}

SeaBattlePlayer* Game::getLoser()
{
    return passivePlayer.lock().get();
}

void Game::generatePlayers()
{
    if(gamemode == GameMode::PVP)
    {
        playerOne = std::make_shared<SeaBattlePlayer>(1, 10, 10, firstPlayerName);
        playerTwo = std::make_shared<SeaBattlePlayer>(2, 10, 10, secondPlayerName);
    }
    if(gamemode == GameMode::PVE)
    {
        playerOne = std::make_shared<SeaBattlePlayer>(1, 10, 10, firstPlayerName);
        playerTwo = std::make_shared<SeaBattleBot>(2, 10, 10, secondPlayerName, botDifficulty);

        std::dynamic_pointer_cast<SeaBattleBot>(playerTwo)->setEnemyField(playerOne->field.get());
    }
        
    if(gamemode == GameMode::EVE)
    {
        playerOne = std::make_shared<SeaBattleBot>(1, 10, 10, firstPlayerName, botDifficulty);
        playerTwo = std::make_shared<SeaBattleBot>(2, 10, 10, secondPlayerName, botDifficulty);

        std::dynamic_pointer_cast<SeaBattleBot>(playerOne)->setEnemyField(playerTwo->field.get());
        std::dynamic_pointer_cast<SeaBattleBot>(playerTwo)->setEnemyField(playerOne->field.get());
    }
        
    activePlayer = playerOne;
    passivePlayer = playerTwo;
}

void Game::generatePlayersFields()
{
    playerOne->generateBattleField();

    playerOneField = playerOne->field.get();
    
    playerTwo->generateBattleField();

    playerTwoField = playerTwo->field.get();

    fieldSize = playerTwo->field.get()->getHeight() * playerTwo->field.get()->getWidth();
}

bool Game::areCoordinatesValid(int x, int y)
{
    return passivePlayer.lock()->canHitAtFieldLocation(x, y);
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
            return;
        }
        if(cell.hasShip&& !cell.wasShot)
        {
            std::cout << shipSymbol;
            return;
        }
        if(!cell.hasShip&& cell.wasShot)
        {
            std::cout << destroyedWaterSymbol;
            return;
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
            std::cout <<  destroyedShipSymbol;
        }
        else if(!cell.hasShip&& cell.wasShot)
        {
            std::cout << destroyedWaterSymbol;
        }
        else
        {
            std::cout << waterSymbol;
        }
    }
}

void Game::drawWinner(SeaBattlePlayer* winner)
{
    std::cout << "Winner: " << winner->username << std::endl;
}