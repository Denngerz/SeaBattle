#pragma once

#include <vector>

struct cell {
    bool hasShip;
    bool wasShot;
};

class Field
{
public:
    Field(unsigned int seedValue, int new_width = 10, int new_height = 10);
    
    unsigned int seed;

    void generate();

    bool isAnyShipsLeft();

    void implementHitAtLocation(const int x, const int y);

    bool gotHit();
    
    bool smShipGotShot = false;
    
    bool canShootAtLocation(int shootX, int shootY);

    std::vector<std::vector<cell>> getField() const;

    int getHeight() const;

    int getWidth() const;
    
private:
    std::vector<std::vector<cell>> field;

    const int width;
    
    const int height;
    
    const char shipSymbol = 'S';
    int shipsAmmount = 10;

    const char waterSymbol = '.';
    
    const char destroyedLocationSymbol = '#';
    const char destroyedShipSymbol = 'D';

    void generateField();
    void generateShips();

    bool canSpawnShipInLocation(const int shipX, const int shipY);
};
