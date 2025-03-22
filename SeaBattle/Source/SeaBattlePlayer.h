#pragma once

#include <memory>
#include <string>
#include <vector>

class Field;
struct Cell;

class SeaBattlePlayer
{

public:
    SeaBattlePlayer(unsigned int seedValue, int field_height = 10, int field_width = 10, std::string name = "");

    virtual ~SeaBattlePlayer() {}

    std::string username;
    
    std::unique_ptr<Field> field;

    void generateBattleField();

    void applyHitToField(const int hitX, const int hitY);

    bool canHitAtFieldLocation(int x, int y) const;

    bool isAnyShipsLeftOnField() const;

    bool isAnyShipGotShot() const;

    int getFieldHeight() const;

    int getFieldWidth() const;

    std::vector<std::vector<Cell>> getFieldVector() const;
};
