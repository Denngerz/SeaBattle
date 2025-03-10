#pragma once
#include <nlohmann/json.hpp>

class PlayerStatsManager
{
public:
    PlayerStatsManager(std::string filePath);
    
    void createNewUser(std::string username, std::string password);
    void updateUserName(std::string username, std::string newName);
    void updatePassword(std::string username, std::string oldPassword, std::string newPassword);
    void deleteUser(std::string username, std::string password);
    int getUserMMR(std::string username);
    double getUserWinrate(std::string username);
    int getUserLostAmmount(std::string username);
    int getUserWonAmmount(std::string username);
    void updatePlayerStats(std::string username, bool didPlayerWin, int ammountOfMoves, int fieldSize);
    bool isPasswordRight(std::string username, std::string password);

private:
    std::string filePath;
    
    static nlohmann::json playerStats;

    void LoadStats();

    void SaveStats(const nlohmann::json& data);

    int basicMMRModifier = 20;
};
