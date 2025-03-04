#include "Field.h"
#include <iostream>

Field::Field(unsigned int seedValue, int new_width, int new_height): width(new_width), height(new_height)
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
    field.resize(height, std::vector<cell>(width));
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

        field[shipY][shipX].hasShip = true; 
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
            if (field[i][j].hasShip)
            {
                return false; 
            }
        }
    }
    return true;
}

bool Field::canShootAtLocation(int shootX, int shootY)
{
    smShipGotShot = false;
    return shootX >= 0 && shootX < width && shootY >= 0 && shootY < height && !field[shootY][shootX].wasShot;
}

std::vector<std::vector<cell>> Field::getField() const
{
    return field;
}

int Field::getHeight() const
{
    return height;
}

int Field::getWidth() const
{
    return width;
}

bool Field::isAnyShipsLeft()
{
    return shipsAmmount > 0;
}

void Field::implementHitAtLocation(const int x, const int y)
{
    if(field[y][x].hasShip)
    {
        shipsAmmount--;
        smShipGotShot = true;
    }
    else
    {
        smShipGotShot = false;
    }

    field[y][x].wasShot = true;
}

bool Field::gotHit()
{
    return smShipGotShot;
}




