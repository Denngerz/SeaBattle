#include "Field.h"
#include <iostream>

Field::Field(unsigned int seedValue, int new_width, int new_height): width(new_width), height(new_height)
{
    seed = seedValue;
}

//====================Field generation====================//
void Field::generate()
{
    generateField();
    tryGenerateShips();
}

void Field::generateField()
{
    field.resize(height, std::vector<Cell>(width));
}


void Field::tryGenerateShips()
{
    srand(seed);
    
    for (int i = 0; i < initialShipsAmmount; ++i)
    {
        int shipX = rand() % width;
        int shipY = rand() % height;

        int counter = 0;
        bool wasAbleToSpawn = true;
        
        while (!canSpawnShipInLocation(shipX, shipY))
        {
            shipX = rand() % width;
            shipY = rand() % height;

            counter++;
            
            if(counter >= 20)
            {
                wasAbleToSpawn = false;
                for(int l = 0; l < height; ++l)
                {
                    for(int j = 0; j < width; ++j)
                    {
                        if(canSpawnShipInLocation(j,l))
                        {
                            shipX = j;
                            shipY = l;
                            
                            wasAbleToSpawn = true;
                        }
                    }
                }
            }
        }

        if(wasAbleToSpawn)
        {
            field[shipY][shipX].hasShip = true;
            shipsAmmount++;
        }
    }
}

//====================Bool checks====================//
bool Field::canSpawnShipInLocation(const int shipX, const int shipY) const
{
    int radius = 1;

    int minXValue = shipX - radius;
    int maxXValue = shipX + radius;

    int minYValue = shipY - radius;
    int maxYValue = shipY + radius;
    
    int minX = (minXValue) >= 0 ? minXValue : 0;
    int maxX = (maxXValue) <= (width - 1) ? maxXValue : width - 1;

    int minY = (minYValue) >= 0 ? minYValue : 0;
    int maxY = (maxYValue) <= (height - 1) ? maxYValue : height - 1;

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
    if(shootX >= 0 && shootX < width && shootY >= 0 && shootY < height)
    {
        return !field[shootY][shootX].wasShot;
    }
    
    return false;
}

bool Field::isAnyShipsLeft() const
{
    return shipsAmmount > 0;
}

//====================Getters====================//
std::vector<std::vector<Cell>> Field::getField() const
{
    return field;
}

Cell Field::getCellAt(int x, int y) const
{
    return field[y][x];
}

int Field::getHeight() const
{
    return height;
}

int Field::getWidth() const
{
    return width;
}

//====================Implementing shots====================//
void Field::implementHitAtLocation(const int x, const int y)
{
    smShipGotShot = false;
    
    if(field[y][x].hasShip)
    {
        shipsAmmount--;
        smShipGotShot = true;
    }

    field[y][x].wasShot = true;
}