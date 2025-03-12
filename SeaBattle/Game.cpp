#include "Game.h"

#include <fstream>
#include <iostream>
#include "Field.h"
#include "SeaBattleBot.h"
#include "SeaBattlePlayer.h"

const gameMode Game::pvp = {GamemodeNames::PVP};
const gameMode Game::pve = {GamemodeNames::PVE};
const gameMode Game::eve = {GamemodeNames::EVE};

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
        passivePlayerField->implementHitAtLocation(shootX, shootY);
        wasShotValid = true;
        ammountOfMoves++;
    }
    else
    {
        wasShotValid = false;
    }
    
    if(!passivePlayerField->isAnyShipsLeft())
    {
        smbLostAllShips = true;
        drawField();
        
        updatePlayersStats(activePlayer.lock().get(), passivePlayer.lock().get(), ammountOfMoves);
        savePlayersDB();

        drawWinner(activePlayer.lock().get());
    }

    if(!passivePlayerField->smShipGotShot && wasShotValid)
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

    if(currentMode.name == GamemodeNames::PVP)
    {
        showFirstPlayerField = false;

        showSecondPlayerField = false;
    }

    if(currentMode.name == GamemodeNames::PVE)
    {
        showFirstPlayerField = true; 

        showSecondPlayerField = false; 
    }

    if(currentMode.name == GamemodeNames::EVE)
    {
        showFirstPlayerField = true; 

        showSecondPlayerField = true; 
    }
}

void Game::changeActivePlayer()
{
    std::swap(activePlayer, passivePlayer);

    changeActiveField();
}

void Game::draw()
{
    if (gameModeSet)
    {
        if(firstPlayerCreated)
        {
            if(secondPlayerCreated)
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
                        std::cout << activePlayer.lock()->username << " turn"<< std::endl;
                        std::cout << "Enter shoot location (x, y): ";
                    }
                }
            }
            else
            {
                std::cout << "\nEnter second player name: ";
            }
        }
        else
        {
            std::cout << "\nEnter first player name: " << std::endl;
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
        if(currentMode.name == GamemodeNames::PVP)
        {
            playerOne = std::make_shared<SeaBattlePlayer>(1, 10, 10);
            playerTwo = std::make_shared<SeaBattlePlayer>(2, 10, 10);
        }
        
        if(currentMode.name == GamemodeNames::PVE)
        {
            draw();
            playerOne = std::make_shared<SeaBattlePlayer>(1, 10, 10);
            playerTwo = std::make_shared<SeaBattleBot>(2, 10, 10, "Bot");
            
            secondPlayerCreated = true;
        }
        
        if(currentMode.name == GamemodeNames::EVE)
        {
            playerOne = std::make_shared<SeaBattleBot>(1, 10, 10, "Bot1");
            playerTwo = std::make_shared<SeaBattleBot>(2, 10, 10, "Bot2");
            
            firstPlayerCreated = true;
            secondPlayerCreated = true;
        }

        setPlayers();
        
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

    changeActiveField();
}

void Game::changeActiveField()
{
    activePlayerField = activePlayer.lock()->field.get();
    passivePlayerField = passivePlayer.lock()->field.get();
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
    return passivePlayerField->canShootAtLocation(x, y);
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
            std::cout <<  destroyedShipSymbol;
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

void Game::drawWinner(SeaBattlePlayer* winner)
{
    std::cout << "Winner: " << winner->username << std::endl;
}

void Game::setPlayers()
{
    std::ifstream file(playerDBPath);
    file >> playersDB;
    
    if(!firstPlayerCreated)
    {
        draw();
        
        std::string firstPlayerUsername;
        std::cin >> firstPlayerUsername;
        
        bool foundProfile = false;
            
        for(auto& player: playersDB["players"])
        {
            if (player["username"] == firstPlayerUsername)
            {
                playerOne->deserialize(player);
                foundProfile = true;
                break;
            }
        }

        if(!foundProfile)
        {
            createNewProfile(firstPlayerUsername);
            savePlayersDB();
            
            for(auto& player: playersDB["players"]){
                if (player["username"] == firstPlayerUsername)
                {
                    playerOne->deserialize(player);
                    foundProfile = true;
                    break;
                }
            }
        }

        firstPlayerCreated = true;
        
        file.close();
    }

    if(!secondPlayerCreated)
    {
        draw();
        
        std::string secondPlayerUsername;
        std::cin >> secondPlayerUsername;
        
        bool foundProfile = false;
            
        for(auto& player: playersDB["players"])
        {
            if (player["username"] == secondPlayerUsername)
            {
                playerTwo->deserialize(player);
                foundProfile = true;
                break;
            }
        }

        if(!foundProfile)
        {
            createNewProfile(secondPlayerUsername);
            savePlayersDB();

            for(auto& player: playersDB["players"])
            {
                if (player["username"] == secondPlayerUsername)
                {
                    playerTwo->deserialize(player);
                    foundProfile = true;
                    break;
                }
            }
        }

        secondPlayerCreated = true;
        
        file.close();
    }
}


void Game::createNewProfile(std::string username)
{
    playersDB["players"].push_back({
       {"username", username},
       {"mmr", 0},
       {"winrate", 0.0},
       {"lost", 0},
       {"won", 0}
    });
}

void Game::savePlayersDB()
{
    std::ofstream outFile(playerDBPath);
    
    outFile << playersDB.dump(4);
    
    outFile.close();
}

void Game::updatePlayersStats(SeaBattlePlayer* winner, SeaBattlePlayer* loser, int moves)
{
    int fieldSize = playerOneField->getHeight() * playerOneField->getWidth();

    if(!dynamic_cast<SeaBattleBot*>(winner))
    {
        winner->won++;
        winner->winRate = (winner->lost == 0) ? 1.0 : static_cast<double>(winner->won) / winner->lost;
        winner->mmr = winner->mmr + defaultMMRBonus + 5 * (1 - moves / fieldSize);

        updatePlayerStatsInFile(winner);
    }

    if(!dynamic_cast<SeaBattleBot*>(loser))
    {
        loser->lost++;
        loser->winRate = (loser->lost == 0) ? 0.0 : static_cast<double>(loser->won) / loser->lost;
        loser->mmr = loser->mmr - defaultMMRBonus;

        updatePlayerStatsInFile(loser);
    }
}

void Game::updatePlayerStatsInFile(SeaBattlePlayer* currentPlayer)
{
    for(auto& player: playersDB["players"])
    {
        if(player["username"] == currentPlayer->username)
        {
            player["winrate"] = currentPlayer->winRate;
            player["mmr"] = currentPlayer->mmr;
            player["lost"] = currentPlayer->lost;
            player["won"] = currentPlayer->won;
            break;
        }
    }
}


