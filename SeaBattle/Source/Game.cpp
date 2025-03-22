#include "Game.h"
#include <iostream>
#include <iomanip>
#include "Field.h"
#include "SeaBattleBot.h"
#include "SeaBattlePlayer.h"

Game::Game(bool isFirstPlayerBot, bool isSecondPlayerBot, std::string chosenFirstPlayerName, std::string chosenSecondPlayerName, BotDifficulty chosenBotDifficulty, bool showFirstPlayer, bool showSecondPlayer):isFirstPlayerBot(isFirstPlayerBot), isSecondPlayerBot(isSecondPlayerBot)
{
    firstPlayerName = chosenFirstPlayerName;
    secondPlayerName = chosenSecondPlayerName;
    botDifficulty = chosenBotDifficulty;
    showFirstPlayerField = showFirstPlayer;
    showSecondPlayerField = showSecondPlayer;
}

//=====================Game loop=====================//
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

//=====================Game logic=====================//
void Game::logic()
{
    if(auto bot = std::dynamic_pointer_cast<SeaBattleBot>(activePlayer.lock()))
    {
        std::tie(shootX, shootY) = bot->generateShootLocations();
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
}

//=====================Input=====================//
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

//=====================Generate methods=====================//
void Game::generate()
{
    generatePlayers();
    generatePlayersFields();
}

void Game::generatePlayers()
{
    playerOne = isFirstPlayerBot
    ? std::make_shared<SeaBattleBot>(1, 10, 10, firstPlayerName, botDifficulty)
    : std::make_shared<SeaBattlePlayer>(1, 10, 10, firstPlayerName);

    playerTwo = isSecondPlayerBot
        ? std::make_shared<SeaBattleBot>(2, 10, 10, secondPlayerName, botDifficulty)
        : std::make_shared<SeaBattlePlayer>(2, 10, 10, secondPlayerName);
    
    if (auto botOne = std::dynamic_pointer_cast<SeaBattleBot>(playerOne))
    {
        botOne->setEnemyField(playerTwo->field.get());
    }

    if (auto botTwo = std::dynamic_pointer_cast<SeaBattleBot>(playerTwo))
    {
        botTwo->setEnemyField(playerOne->field.get());
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
}

void Game::changeActivePlayer()
{
    std::swap(activePlayer, passivePlayer);
}

//=====================Bool checks=====================//
bool Game::isRoundOver()
{
    return smbLostAllShips;
}

bool Game::areCoordinatesValid(int x, int y)
{
    return passivePlayer.lock()->canHitAtFieldLocation(x, y);
}

bool Game::didfirstPlayerWin()
{
    if(activePlayer.lock() == playerOne)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//=====================Draw methods=====================//
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

void Game::drawVisibleCell(Cell& cell)
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

void Game::drawUnvisibleCell(Cell& cell)
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


void Game::drawCell(Cell cell, bool isVisible)
{
    if(isVisible)
    {
        drawVisibleCell(cell);
    }
    else
    {
        drawUnvisibleCell(cell);
    }
}

void Game::drawWinner(SeaBattlePlayer* winner)
{
    std::cout << "Winner: " << winner->username << std::endl;
}