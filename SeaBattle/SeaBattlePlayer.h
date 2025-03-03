#pragma once

#include "Field.h"

class SeaBattlePlayer
{

public:
    SeaBattlePlayer(unsigned int seedValue, int field_height = 10, int field_width = 10);

    Field field;

    void generateBattleField();

    void applyHitToField(const int hitX, const int hitY);

    bool canHitAtFieldLocation(int x, int y);

    bool isAnyShipsLeftOnField();

    bool isAnyShipGotShot();

    int getFieldHeight();

    int getFieldWidth();

    std::vector<std::vector<cell>> getFieldVector() const;
};
