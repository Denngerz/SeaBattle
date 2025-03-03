#include "SeaBattlePlayer.h"

SeaBattlePlayer::SeaBattlePlayer(unsigned int seedValue): field(seedValue)
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

void SeaBattlePlayer::drawField()
{
    field.draw();
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



