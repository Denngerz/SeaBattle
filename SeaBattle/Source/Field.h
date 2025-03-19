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

    bool isAnyShipsLeft() const;

    void implementHitAtLocation(const int x, const int y);
    
    bool smShipGotShot = false;
    
    bool canShootAtLocation(int shootX, int shootY);

    std::vector<std::vector<cell>> getField() const;

    cell getCellAt(int x, int y) const;

    int getHeight() const;

    int getWidth() const;
    
private:
    std::vector<std::vector<cell>> field;

    const int width;
    
    const int height;
    
    int shipsAmmount;

    int initialShipsAmmount = 10;

    void generateField();
    
    void tryGenerateShips();

    bool canSpawnShipInLocation(const int shipX, const int shipY) const;
};
