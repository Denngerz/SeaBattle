#pragma once
#include "SeaBattlePlayer.h"
#include "GameEnums.h"

class SeaBattleBot : public SeaBattlePlayer
{
public:
    SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name, BotDifficulty difficulty);

    void generateShootLocations();

    int hitChance;

    BotDifficulty currentDifficulty;

    void setEnemyField(Field* shootingField);
    
    int getShootX() const;
    int getShootY() const;
    
private:
    int shootX, shootY;

    void setHitChanceBasedOnDifficulty();

    Field* enemyField;
};
