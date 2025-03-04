#pragma once
#include "SeaBattlePlayer.h"

class SeaBattleBot : public SeaBattlePlayer
{
public:
    SeaBattleBot(unsigned int seedValue, int field_height, int field_width): SeaBattlePlayer(seedValue, field_height, field_width) {}

    void generateShootLocations();

    int getShootX() const;
    int getShootY() const;
    
private:
    int shootX, shootY;
    
};
