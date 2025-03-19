#include "SeaBattlePlayer.h"
#include "Field.h"

SeaBattlePlayer::SeaBattlePlayer(unsigned int seedValue, int field_height, int field_width, std::string name)
{
    field = std::make_unique<Field>(seedValue, field_width, field_height);
    username = name;
}

void SeaBattlePlayer::generateBattleField()
{
    field->generate();
}

void SeaBattlePlayer::applyHitToField(const int hitX, const int hitY)
{
    field->implementHitAtLocation(hitX, hitY);
}

bool SeaBattlePlayer::canHitAtFieldLocation(int x, int y) const
{
    return field->canShootAtLocation(x, y);
}

bool SeaBattlePlayer::isAnyShipsLeftOnField() const
{
    return field->isAnyShipsLeft();
}

bool SeaBattlePlayer::isAnyShipGotShot() const
{
    return field->smShipGotShot;
}

int SeaBattlePlayer::getFieldHeight() const
{
    return field->getHeight();
}

int SeaBattlePlayer::getFieldWidth() const
{
    return field->getWidth();
}

std::vector<std::vector<cell>> SeaBattlePlayer::getFieldVector() const
{
    return field->getField();
}



