#include "SeaBattleBot.h"
#include "Field.h"

SeaBattleBot::SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name, int shipShootChance): SeaBattlePlayer(seedValue, field_height, field_width)
{
    username = name;
    shootChance = shipShootChance;
}

void SeaBattleBot::generateShootLocations()
{
    bool didShoot = false;
    
    if(rand() % 101 <= shootChance)
    {
        for(int i = 0; i < getFieldHeight(); i++)
        {
            for(int j = 0; j < getFieldWidth(); j++)
            {
                std::vector<std::vector<cell>> cells = enemyField->getField();
                if(cells[i][j].hasShip && !cells[i][j].wasShot)
                {
                    shootX = j + 1;
                    shootY = i + 1;
                    didShoot = true;
                    break;
                }
            }
            if(didShoot)
            {
                break;
            }
        }
    }
    else
    {
        for(int i = 0; i < getFieldHeight(); i++)
        {
            for(int j = 0; j < getFieldWidth(); j++)
            {
                std::vector<std::vector<cell>> cells = enemyField->getField();
                if(!cells[i][j].hasShip && !cells[i][j].wasShot)
                {
                    shootX = j + 1;
                    shootY = i + 1;
                    didShoot = true;
                    break;
                }
            }
            if(didShoot)
            {
                break;
            }
        }
    }
}

void SeaBattleBot::setEnemyField(Field* shootingField)
{
    enemyField = shootingField;
}

int SeaBattleBot::getShootX() const
{
    return shootX;
}

int SeaBattleBot::getShootY() const
{
    return shootY;
}


