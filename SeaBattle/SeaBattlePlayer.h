#pragma once

#include "Field.h"

class SeaBattlePlayer
{

public:
    SeaBattlePlayer(unsigned int seedValue);

    Field field;

    void generateBattleField();

    void applyHitToField(const int hitX, const int hitY);

    void drawField();

    bool canHitAtFieldLocation(int x, int y);

    bool isAnyShipsLeftOnField();

    bool isAnyShipGotShot();
};
