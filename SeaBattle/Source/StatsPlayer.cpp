#include "StatsPlayer.h"
#include <fstream>
#include <iostream>

StatsPlayer::StatsPlayer(std::string name, std::string filename)
{
    username = name;
    playersDBFilename = filename;
}

nlohmann::json StatsPlayer::serialize() const
{
    return {
                    {"username", username},
                    {"mmr", mmr},
                    {"winrate", winrate},
                    {"won", won},
                    {"lost", lost},
        };
}

void StatsPlayer::deserialize(const nlohmann::json& j) 
{
    username = j["username"];
    mmr = j["mmr"];
    winrate = j["winrate"];
    won = j["won"];
    lost = j["lost"];
}

void StatsPlayer::setStatsPlayer()
{
    if(!playersFileExits())
    {
        createPlayersFile();
    }

    std::ifstream file(playersDBFilename);
    nlohmann::json data;

    if(file.is_open())
    {
        file >> data;
        
        file.close();
    }
    
    for(auto& player: data["players"])
    {
        if(player["username"] == username)
        {
            deserialize(player);
            return;
        }
    }
        
    data["players"].push_back(serialize());
    
    saveDataToFile(playersDBFilename, data);
}

void StatsPlayer::updatePlayerStats(bool didWin, int ammountOfMoves, int defaultMMRBonus, int fieldSize, StatsPlayer* enemyPlayer)
{
    //====Win probabilities====//
    double P_A = winrate / 100.0;
    double P_B = enemyPlayer->winrate / 100.0;
    
    if (P_A == 0) P_A = 0.01;
    if (P_B == 0) P_B = 0.01;

    //====Total bet (MMR)====//
    double totalBet = mmr + enemyPlayer->mmr;
    if (totalBet == 0) totalBet = 1;
    
    double betA = mmr;
    double betB = enemyPlayer->mmr;

    if (didWin)
    {
        won++;
        mmr += (totalBet * P_A) - (betA * P_B);
    }
    else
    {
        lost++;
        mmr -= (totalBet * P_B) - (betB * P_A);
    }
    
    if (mmr < 0) mmr = 0;
    
    winrate = ((won + lost == 0) ? 100.0 : (static_cast<double>(won) / (won + lost)) * 100.0);

    std::ifstream file(playersDBFilename);
    nlohmann::json data;

    if(file.is_open())
    {
        file >> data;
        
        file.close();
    }
    
    for(auto& player: data["players"])
    {
        if(player["username"] == username)
        {
            player = serialize();
            break;
        }
    }

    saveDataToFile(playersDBFilename, data);
}

bool StatsPlayer::playersFileExits()
{
    std::ifstream file(playersDBFilename);

    return file.good();
}

void StatsPlayer::createPlayersFile()
{
    nlohmann::json defaultData;
    defaultData["players"] = nlohmann::json::array();
        
    std::ofstream outFile(playersDBFilename);
    if (outFile.is_open())
    {
        outFile << defaultData.dump(4);
        outFile.close();
    }
}

void StatsPlayer::saveDataToFile(std::string filename, nlohmann::json data)
{
    std::ofstream file(playersDBFilename);
    if (!file.is_open()) {
        return;
    }

    file << data.dump(4);
    file.close();
}


