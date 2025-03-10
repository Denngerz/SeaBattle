#pragma once

#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

class Field;
struct cell;

class SeaBattlePlayer
{

public:
    SeaBattlePlayer(unsigned int seedValue, int field_height = 10, int field_width = 10);

    unsigned int seed;
    
    std::string username;
    
    int MMR = 0;
    
    double winRate = 0;
    
    int won = 0;
    
    int lost = 0;

    virtual ~SeaBattlePlayer() {}

    std::unique_ptr<Field> field;

    void generateBattleField();

    int getFieldHeight() const;

    int getFieldWidth() const;

    std::vector<std::vector<cell>> getFieldVector() const;

    nlohmann::json serialize() const;

    void deserialize(const nlohmann::json& j);
};
