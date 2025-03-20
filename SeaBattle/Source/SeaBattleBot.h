#pragma once
#include "SeaBattlePlayer.h"
#include "GameEnums.h"

class SeaBattleBot : public SeaBattlePlayer
{
public:
    SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name, BotDifficulty difficulty);

    std::tuple<int, int> generateShootLocations();

    BotDifficulty currentDifficulty;

    void setEnemyField(Field* shootingField);
    
private:
    //==============Field==============//
    int shootX, shootY;

    std::vector<std::pair<int, int>> shotLocations;

    bool wasShotBefore(int x, int y) const;
    
    Field* enemyField;

    std::tuple<int, int> findNewLocation(bool shouldContainShip);

    //==============Bot settings==============//
    int switchChance = 15;
};
