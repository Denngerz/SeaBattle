#pragma once

#include "Field.h"
#include <vector>

#include "Game.h"

class SeaBattlePlayer
{

public:
    SeaBattlePlayer(unsigned int seedValue);

    Field field;

    void generateBattleField();

    void applyHitToField(const int hitX, const int hitY);

private:
   
};
