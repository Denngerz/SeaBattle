#include "SeaBattleBot.h"
#include "Field.h"

SeaBattleBot::SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name): SeaBattlePlayer(seedValue, field_height, field_width)
{
    username = name;
}

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


