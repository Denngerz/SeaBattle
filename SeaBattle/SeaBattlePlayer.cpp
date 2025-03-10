#include "SeaBattlePlayer.h"

#include <fstream>

#include "Field.h"

SeaBattlePlayer::SeaBattlePlayer(unsigned int seedValue, int field_height, int field_width, int id): seed(seedValue), id(id)
{
    field = std::make_unique<Field>(seedValue, field_width, field_height);
}

void SeaBattlePlayer::generateBattleField()
{
    field->generate();
}

int SeaBattlePlayer::getFieldHeight() const
{
    return field->getHeight();
}

int SeaBattlePlayer::getFieldWidth() const
{
    return field->getWidth();
}

std::vector<std::vector<cell>> SeaBattlePlayer::getFieldVector() const
{
    return field->getField();
}

nlohmann::json SeaBattlePlayer::serialize() const
{
    return {
                {"username", username},
                {"password", password},
                {"MMR", MMR},
                {"winRate", winRate},
                {"won", won},
                {"lost", lost},
    };
}

void SeaBattlePlayer::deserialize(const nlohmann::json& j) 
{
    username = j["username"];
    password = j["password"];
    MMR = j["MMR"];
    winRate = j["winRate"];
    lost = j["lost"];
}

void SeaBattlePlayer::saveToFile(const std::string& filePath)
{
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << serialize();
        file.close();
    }
}

void SeaBattlePlayer::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    nlohmann::json j;
    if (file.is_open()) {
        file >> j;
        file.close();
    }
    return deserialize(j);
}


