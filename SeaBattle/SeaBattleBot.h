#pragma once
#include "SeaBattlePlayer.h"

class SeaBattleBot : public SeaBattlePlayer
{
public:
    SeaBattleBot(unsigned int seedValue, int field_height, int field_width, std::string name);

    void generateShootLocations();

    int getShootX() const;
    int getShootY() const;
    
private:
    int shootX, shootY;
    
};
