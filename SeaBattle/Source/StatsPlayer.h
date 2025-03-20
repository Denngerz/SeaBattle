#pragma once

#include "../ThirdParty/nlohmann/json.hpp"

class StatsPlayer
{
public:
    StatsPlayer(std::string name, std::string filename);
    
    std::string username;
    
    int mmr = 1;
    
    int won = 0;
    
    int lost = 0;   
    
    double winrate = 0.0;

    nlohmann::json serialize() const;

    void deserialize(const nlohmann::json& j);

    void setStatsPlayer();

    void updatePlayerStats(bool didWin, int ammountOfMoves, int defaultMMRBonus, int fieldSize, StatsPlayer* enemyPlayer);

private:
    bool playersFileExits();

    void createPlayersFile();

    void saveDataToFile(std::string filename, nlohmann::json data);

    std::string playersDBFilename;
};
