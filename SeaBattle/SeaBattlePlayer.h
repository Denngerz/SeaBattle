#pragma once

#include <vector>

class SeaBattlePlayer
{

private:
    std::vector<std::vector<char>> field;
    const int width = 10;
    const int height = 10;
    const char shipSymbol = 'S';
    int shipsAmmount = 1;
    const char destroyedLocationSymbol = '#';
    const char destroyedShipSymbol = 'D';
    unsigned int seed;
    
public:
    SeaBattlePlayer(unsigned int seedValue);
    
    int shootX, shootY;
    
    void generate();
    
    void generateField();
    
    void generateShips();
    
    bool canSpawnShipInLocation(const int shipX, const int shipY);
    
    void draw();
    
    bool isEndGame();
    
    void getInput();
    
    void implementHitAtLocation(const int x, const int y);
    
    bool isShootableLocation(const int x, const int y);
    
    void logic(SeaBattlePlayer& enemyPlayer);
};
