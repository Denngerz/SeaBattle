#include "SeaBattleBot.h"
#include "Field.h"

SeaBattleBot::SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name, BotDifficulty difficulty): SeaBattlePlayer(seedValue, field_height, field_width, name)
{
    currentDifficulty = difficulty;
    setHitChanceBasedOnDifficulty();
}

void SeaBattleBot::generateShootLocations()
{
    bool didShoot = false;
    
    if(rand() % 101 <= hitChance)
    {
        for(int i = 0; i < getFieldHeight(); i++)
        {
            for(int j = 0; j < getFieldWidth(); j++)
            {
                std::vector<std::vector<cell>> cells = enemyField->getField();
                if(cells[i][j].hasShip && !cells[i][j].wasShot)
                {
                    shootX = j;
                    shootY = i;
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
                    shootX = j;
                    shootY = i;
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

int SeaBattleBot::getShootX() const
{
    return shootX;
}

int SeaBattleBot::getShootY() const
{
    return shootY;
}

void SeaBattleBot::setHitChanceBasedOnDifficulty()
{
    switch (currentDifficulty)
    {
    case BotDifficulty::EASY:
        hitChance = 10;
        break;
        
    case BotDifficulty::NORMAL:
        hitChance = 15;
        break;
        
    case BotDifficulty::HARD:
        hitChance = 20;
        break;
        
    default:
        break;
    }
}

void SeaBattleBot::setEnemyField(Field* shootingField)
{
    enemyField = shootingField;
}


