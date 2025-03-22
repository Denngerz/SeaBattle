#include "SeaBattleBot.h"
#include <tuple>
#include "Field.h"

SeaBattleBot::SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name, BotDifficulty difficulty): SeaBattlePlayer(seedValue, field_height, field_width, name)
{
    currentDifficulty = difficulty;
}

std::tuple<int, int> SeaBattleBot::generateShootLocations()
{
    do
    {
        shootX = rand() % getFieldWidth();
        shootY = rand() % getFieldHeight();
    }
    while (wasShotBefore(shootX, shootY));
    
    if (currentDifficulty != BotDifficulty::NORMAL)
    {
        bool shouldSwitchLocation = (rand() % 101) <= switchChance;
        
        if (shouldSwitchLocation)
        {
            bool shouldContainShip = (currentDifficulty == BotDifficulty::HARD);
            std::tie(shootX, shootY) = findNewLocation(shouldContainShip);
        }
    }
    
    shotLocations.insert(std::make_pair(shootX, shootY));

    return std::make_tuple(shootX, shootY);
}

void SeaBattleBot::setEnemyField(Field* shootingField)
{
    enemyField = shootingField;
}

bool SeaBattleBot::wasShotBefore(int x, int y) const {
    return shotLocations.find(std::make_pair(x, y)) != shotLocations.end();
}

std::tuple<int, int> SeaBattleBot::findNewLocation(bool shouldContainShip)
{
    int x;
    int y;

    do
    {
        x = rand() % getFieldWidth();
        y = rand() % getFieldHeight();
    }
    while (enemyField->getCellAt(x, y).hasShip != shouldContainShip);

    return std::make_tuple(x, y);
}



