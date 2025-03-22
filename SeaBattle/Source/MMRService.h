#pragma once
#include "StatsPlayer.h"

class MMRService
{
public:
    static void updatePlayer(StatsPlayer* playerOne, StatsPlayer* playerTwo, bool firstPlayerWon);
    static void savePlayersCurrentStats(StatsPlayer* playerOne, StatsPlayer* playerTwo);
};
