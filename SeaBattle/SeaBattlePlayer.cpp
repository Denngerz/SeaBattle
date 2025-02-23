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


