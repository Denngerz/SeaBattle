#include "StatsPlayer.h"
#include <fstream>

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

void StatsPlayer::updatePlayerStats(bool didWin, int ammountOfMoves, int defaultMMRBonus, int fieldSize)
{
    if(didWin)
    {
        won++;
        winrate = (lost == 0) ? 1.0 : static_cast<double>(won) / lost;
        mmr = mmr + defaultMMRBonus + 5 * (1 - ammountOfMoves / fieldSize);
    }
    else
    {
        lost++;
        winrate = (lost == 0) ? 1.0 : static_cast<double>(won) / lost;
        mmr = (mmr - defaultMMRBonus) <= 0 ? 0 : mmr - defaultMMRBonus;
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


