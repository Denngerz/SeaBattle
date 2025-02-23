#pragma once

#include <vector>

struct cell {
    int x;
    int y;
    char symbol;
};

class Field
{
public:
    Field(unsigned int seedValue);
    
    std::vector<std::vector<cell>> field;
    
    const int width = 10;
    const int height = 10;
    
    unsigned int seed;

    void generate();

    void draw();

    bool isAnyShipsLeft();

    void implementHitAtLocation(const int x, const int y);

    bool gotHit();
    
    bool smShipGotShot;
    
private:
    const char shipSymbol = 'S';
    int shipsAmmount = 10;

    const char waterSymbol = '.';
    
    const char destroyedLocationSymbol = '#';
    const char destroyedShipSymbol = 'D';

    void generateField();
    void generateShips();

    bool canSpawnShipInLocation(const int shipX, const int shipY);
};
