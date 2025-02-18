#include "SeaBattle.h"
#include <vector>
#include <stdlib.h>

// Field
std::vector<std::vector<char>> field;
const int width = 10;
const int height = 10;
const int shipsAmmount = 12;

void generate()
{
   
}

void SeaBattle::generateField()
{
    for(int i = 0; i < height; i++)
    {
        std::vector<char> row(width);
        
        for(int j = 0; j < width; j++)
        {
            char symbol = '.';
            row[j] = symbol;
        }
        
        field.push_back(row);
    }
}

void SeaBattle::generateShips()
{
    
}
