﻿#pragma once

#include <memory>
#include <vector>

class Field;
struct cell;

class SeaBattlePlayer
{

public:
    SeaBattlePlayer(unsigned int seedValue, int field_height = 10, int field_width = 10, int i = 0);

    virtual ~SeaBattlePlayer() {}

    int id;

    std::unique_ptr<Field> field;

    void generateBattleField();

    void applyHitToField(const int hitX, const int hitY);

    bool canHitAtFieldLocation(int x, int y) const;

    bool isAnyShipsLeftOnField() const;

    bool isAnyShipGotShot() const;

    int getFieldHeight() const;

    int getFieldWidth() const;

    std::vector<std::vector<cell>> getFieldVector() const;
};
