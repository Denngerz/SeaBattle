#include "SeaBattlePlayer.h"

SeaBattlePlayer::SeaBattlePlayer(unsigned int seedValue, int field_height, int field_width): field(seedValue, field_height, field_width)
{
}

void SeaBattlePlayer::generateBattleField()
{
    field.generate();
}

void SeaBattlePlayer::applyHitToField(const int hitX, const int hitY)
{
    field.implementHitAtLocation(hitX, hitY);
}

bool SeaBattlePlayer::canHitAtFieldLocation(int x, int y)
{
    return field.canShootAtLocation(x, y);
}

bool SeaBattlePlayer::isAnyShipsLeftOnField()
{
    return field.isAnyShipsLeft();
}

bool SeaBattlePlayer::isAnyShipGotShot()
{
    return field.smShipGotShot;
}

int SeaBattlePlayer::getFieldHeight()
{
    return field.getHeight();
}

int SeaBattlePlayer::getFieldWidth()
{
    return field.getWidth();
}

std::vector<std::vector<cell>> SeaBattlePlayer::getFieldVector() const
{
    return field.getField();
}



