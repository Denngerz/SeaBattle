#include "MMRService.h"

void MMRService::updatePlayer(StatsPlayer* playerOne, StatsPlayer* playerTwo, bool firstPlayerWon)
{
    //====Win probabilities====//
    double P_A = playerOne->winrate / 100.0;
    double P_B = playerTwo->winrate / 100.0;
    
    if (P_A == 0) P_A = 0.01;
    if (P_B == 0) P_B = 0.01;

    //====Total bet (MMR)====//
    double totalBet = playerOne->mmr + playerTwo->mmr;
    if (totalBet == 0) totalBet = 1;
    
    double betA = playerOne->mmr;
    double betB = playerTwo->mmr;

    if (firstPlayerWon)
    {
        playerOne->won++;
        playerOne->mmr += (totalBet * P_A) - (betA * P_B);
        
        playerTwo->lost++;
        playerTwo->mmr -= (totalBet * P_B) - (betB * P_A);
    }
    else
    {
        playerTwo->won++;
        playerTwo->mmr += (totalBet * P_A) - (betA * P_B);
        
        playerOne->lost++;
        playerOne->mmr -= (totalBet * P_B) - (betB * P_A);
    }
    
    if (playerOne->mmr < 0) playerOne->mmr = 0;
    if (playerTwo->mmr < 0) playerTwo->mmr = 0;
    
    playerOne->winrate = ((playerOne->won + playerOne->lost == 0) ? 100.0 : (static_cast<double>(playerOne->won) / (playerOne->won + playerOne->lost)) * 100.0);
    playerTwo->winrate = ((playerTwo->won + playerTwo->lost == 0) ? 100.0 : (static_cast<double>(playerTwo->won) / (playerTwo->won + playerTwo->lost)) * 100.0);

    savePlayersCurrentStats(playerOne, playerTwo);
}

void MMRService::savePlayersCurrentStats(StatsPlayer* playerOne, StatsPlayer* playerTwo)
{
    playerOne->saveCurrentStats();
    playerTwo->saveCurrentStats();
}