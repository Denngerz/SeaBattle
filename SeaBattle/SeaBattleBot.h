#pragma once
#include "SeaBattlePlayer.h"

struct cell;
class Field;

class SeaBattleBot : public SeaBattlePlayer
{
public:
    SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name, int shipShootChance);

    void generateShootLocations();

    void setEnemyField(Field* shootingField);

    int getShootX() const;
    int getShootY() const;
    
private:
    int shootX, shootY;

    int shootChance;

    Field* enemyField;
    
};
