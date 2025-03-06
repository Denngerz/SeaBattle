#include "SeaBattleBot.h"
#include "Field.h"

void SeaBattleBot::generateShootLocations()
{
    shootX = rand() % field->getWidth() + 1;
    shootY = rand() % field->getHeight() + 1;
}

int SeaBattleBot::getShootX() const
{
    return shootX;
}

int SeaBattleBot::getShootY() const
{
    return shootY;
}


