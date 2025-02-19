#include "SeaBattlePlayer.h"
#include <stdlib.h>
#include <iostream>

SeaBattlePlayer::SeaBattlePlayer(unsigned int seedValue) : seed(seedValue) {}

void SeaBattlePlayer::generate()
{
    generateField();
    generateShips();
}


void SeaBattlePlayer::generateField()
{
    field.clear();
    
    for (int i = 0; i < height; i++)
    {
        std::vector<char> row(width, '.');
        field.push_back(row);
    }
}

void SeaBattlePlayer::generateShips()
{
    srand(seed);
    
    for (int i = 0; i < shipsAmmount; ++i)
    {
        int shipX = rand() % width;
        int shipY = rand() % height;
        
        while (!canSpawnShipInLocation(shipX, shipY))
        {
            shipX = rand() % width;
            shipY = rand() % height;
        }

        field[shipY][shipX] = shipSymbol; 
    }
}

bool SeaBattlePlayer::canSpawnShipInLocation(const int shipX, const int shipY)
{
    int radius = 1;

    int minX = (shipX - radius) >= 0 ? shipX - radius : 0;
    int maxX = (shipX + radius) <= (width - 1) ? shipX + radius : width - 1;

    int minY = (shipY - radius) >= 0 ? shipY - radius : 0;
    int maxY = (shipY + radius) <= (height - 1) ? shipY + radius : height - 1;

    for (int i = minY; i <= maxY; i++)
    {
        for (int j = minX; j <= maxX; j++)
        {
            if (field[i][j] == shipSymbol)
            {
                return false; 
            }
        }
    }
    return true;
}

void SeaBattlePlayer::draw()
{
    std::cout << "================================================" << std::endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << field[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "================================================" << std::endl;
}

bool SeaBattlePlayer::isEndGame() {
    return shipsAmmount <= 0;
}


void SeaBattlePlayer::getInput()
{
    std::cin >> shootX;
    std::cin >> shootY;
}

void SeaBattlePlayer::implementHitAtLocation(const int x, const int y)
{
    if(isShootableLocation(x, y))
    {
        if(field[y][x] == shipSymbol)
        {
            shipsAmmount--;
            field[y][x] = destroyedShipSymbol;
        }
        else
        {
            field[y][x] = destroyedLocationSymbol;
        }
    }
}

bool SeaBattlePlayer::isShootableLocation(const int x, const int y)
{
    return x < width && y < height && x >= 0 && y >= 0;
}

void SeaBattlePlayer::logic(SeaBattlePlayer& enemyPlayer)
{
    enemyPlayer.implementHitAtLocation(shootX, shootY);
}
