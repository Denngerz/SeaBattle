#include <iostream>
#include "SeaBattlePlayer.h"



int main(int argc, char* argv[])
{
    unsigned int firstPlayerSeed = static_cast<unsigned int>(time(0));
    unsigned int secondPlayerSeed = firstPlayerSeed + 1;
    
    SeaBattlePlayer firstPlayer(firstPlayerSeed);
    SeaBattlePlayer secondPlayer(secondPlayerSeed);
    firstPlayer.generate();
    secondPlayer.generate();

    while(true)
    {
        std::cout << "First player hits: " << std::endl;
        
        firstPlayer.draw();
        firstPlayer.getInput();
        firstPlayer.logic(secondPlayer);

        if (secondPlayer.isEndGame())
        {
            std::cout << "Second player lost! First player wins!" << std::endl;
            break;
        }
        
        std::cout << "Second player hits: " << std::endl;
        
        secondPlayer.draw();
        secondPlayer.getInput();
        secondPlayer.logic(firstPlayer);

        if (firstPlayer.isEndGame())
        {
            std::cout << "First player lost! Second player wins!" << std::endl;
            break;
        }
    }
    std::cout << "Game Over" <<std::endl;
    
    return 0;
}