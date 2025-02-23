#include "Field.h"
#include <iostream>

Field::Field(unsigned int seedValue)
{
    seed = seedValue;
}

void Field::generate()
{
    generateField();
    generateShips();
}

void Field::generateField()
{
    field.clear();
    
    for (int i = 0; i < height; i++)
    {
        std::vector<cell> row(width);
        for(int j = 0; j < width; j ++)
        {
            row[j].x = j;
            row[j].y = i;
            row[j].symbol = waterSymbol;
        }
        field.push_back(row);
    }
}

void Field::generateShips()
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

        field[shipY][shipX].symbol = shipSymbol; 
    }
}

bool Field::canSpawnShipInLocation(const int shipX, const int shipY)
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
            if (field[i][j].symbol == shipSymbol)
            {
                return false; 
            }
        }
    }
    return true;
}

void Field::draw()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << field[i][j].symbol << " ";
        }
        std::cout << std::endl;
    }
}

bool Field::isAnyShipsLeft()
{
    return shipsAmmount <= 0;
}

void Field::implementHitAtLocation(const int x, const int y)
{
    if(field[y][x].symbol == shipSymbol)
    {
        shipsAmmount--;
        field[y][x].symbol = destroyedShipSymbol;
        smShipGotShot = true;
    }
    else
    {
        field[y][x].symbol = destroyedLocationSymbol;
        smShipGotShot = false;
    }
}

bool Field::gotHit()
{
    return smShipGotShot;
}




