#include "PlayerStatsManager.h"
#include <fstream>

PlayerStatsManager::PlayerStatsManager(std::string filePath): filePath(filePath)
{
    LoadStats();
}

void PlayerStatsManager::createNewUser(std::string username, std::string password)
{
    LoadStats();
    playerStats["players"].push_back({
        {"username", username},
        {"password", password},
        {"MMR", 0},
        {"Winrate", 0},
        {"Lost", 0},
        {"Won", 0}
    });
    SaveStats(playerStats);
}

void PlayerStatsManager::updateUserName(std::string username, std::string newName)
{
    LoadStats();
    bool isUpdated = false;
    
    for (auto& player : playerStats["players"]) {
        if (player["username"] == username) {
            player["username"] = newName;
            isUpdated = true;
            break;
        }
    }

    if(isUpdated)
    {
        SaveStats(playerStats);
    }
}

void PlayerStatsManager::updatePassword(std::string username, std::string oldPassword, std::string newPassword)
{
    LoadStats();
    bool isUpdated = false;

    if(isPasswordRight(username, oldPassword))
    {
        for (auto& player : playerStats["players"]) {
            if (player["username"] == username) {
                player["password"] = newPassword;
                isUpdated = true;
                break;
            }
        }
    }

    if(isUpdated)
    {
        SaveStats(playerStats);
    }
}

void PlayerStatsManager::deleteUser(std::string username, std::string password)
{
    LoadStats();
    bool isUpdated = false;

    if(isPasswordRight(username, password))
    {
        for (auto it = playerStats["players"].begin(); it != playerStats["players"].end(); ++it) {
            if ((*it)["username"] == username) {
                playerStats["players"].erase(it);
                isUpdated = true;
                break;
            }
        }
    }

    if(isUpdated)
    {
        SaveStats(playerStats);
    }
}

int PlayerStatsManager::getUserMMR(std::string username)
{
    LoadStats();

    for (const auto& player : playerStats["players"]) {
        if (player["username"] == username) {
            return player["MMR"];
        }
    }

    return -1;
}

double PlayerStatsManager::getUserWinrate(std::string username)
{
    LoadStats();

    for (const auto& player : playerStats["players"]) {
        if (player["username"] == username) {
            return player["Winrate"];
        }
    }

    return -1;
}

int PlayerStatsManager::getUserLostAmmount(std::string username)
{
    LoadStats();

    for (const auto& player : playerStats["players"]) {
        if (player["username"] == username) {
            return player["Lost"];
        }
    }

    return -1;
}

int PlayerStatsManager::getUserWonAmmount(std::string username)
{
    LoadStats();

    for (const auto& player : playerStats["players"]) {
        if (player["username"] == username) {
            return player["Won"];
        }
    }

    return -1;
}

void PlayerStatsManager::updatePlayerStats(std::string username, bool didPlayerWin, int ammountOfMoves, int fieldSize)
{
    LoadStats();
    bool isUpdated = false;

    for (auto& player : playerStats["players"]) {
        if (player["username"] == username) {
            
            int currentMMR = player["MMR"];
            int lost = player["Lost"];
            int won = player["Won"];
            
            if(didPlayerWin)
            {
                double bonusMMR = basicMMRModifier + 5 * (1 - (ammountOfMoves / fieldSize));
                
                player["MMR"] = static_cast<int>(round(currentMMR + bonusMMR));
                player["Won"] = won + 1;
                player["WinRate"] = won / lost;
                
                isUpdated = true;
                break;
            }
            else
            {
                player["MMR"] = basicMMRModifier + currentMMR;
                player["Lost"] = lost + 1;
                player["WinRate"] = won / lost;
                
                isUpdated = true;
                break;
            }
        }
    }

    if(isUpdated)
    {
        SaveStats(playerStats);
    }
}

bool PlayerStatsManager::isPasswordRight(std::string username, std::string password)
{
    LoadStats();
    
    for (auto& player : playerStats["players"]) {
        if (player["password"] == password && player["username"] == username) {
            return true;
        }
    }
    return false;
}

bool PlayerStatsManager::doesUserExist(std::string username)
{
    for (auto& player : playerStats["players"]) {
        if (player["username"] == username) {
            return true;
        }
    }
    return false;
}

void PlayerStatsManager::LoadStats() {
    std::ifstream file(filePath);
    
    if (file.is_open()) {
        file >> playerStats;
        file.close();
    }
}

void PlayerStatsManager::SaveStats(const nlohmann::json& data) {
    std::ofstream file(filePath);
    
    if (file.is_open()) {
        file << data.dump(4);
        file.close();
    }
}
