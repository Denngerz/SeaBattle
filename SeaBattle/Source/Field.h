#pragma once

#include <vector>

struct Cell {
    bool hasShip;
    bool wasShot;
};

class Field
{
public:
    Field(unsigned int seedValue, int new_width = 10, int new_height = 10);
    
    unsigned int seed;

    void generate();

    //========Bool checks========//
    bool isAnyShipsLeft() const;
    
    bool smShipGotShot = false;
    
    bool canShootAtLocation(int shootX, int shootY);

    //========Getters========//

    std::vector<std::vector<Cell>> getField() const;

    Cell getCellAt(int x, int y) const;

    int getHeight() const;

    int getWidth() const;

    //=========Implement shot=========//
    void implementHitAtLocation(const int x, const int y);
    
private:
    //=========Field vector=========//
    std::vector<std::vector<Cell>> field;

    //=========Field settings=========//
    int initialShipsAmmount = 10;

    const int width;
    
    const int height;

    //=========Field generation========//
    void generateField();
    
    void tryGenerateShips();

    bool canSpawnShipInLocation(const int shipX, const int shipY) const;

    int shipsAmmount;
};
