#include "SeaBattlePlayer.h"
#include "Field.h"

SeaBattlePlayer::SeaBattlePlayer(unsigned int seedValue, int field_height, int field_width): seed(seedValue)
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
                {"mmr", mmr},
                {"winrate", winRate},
                {"won", won},
                {"lost", lost},
    };
}

void SeaBattlePlayer::deserialize(const nlohmann::json& j) 
{
    username = j["username"];
    mmr = j["mmr"];
    winRate = j["winrate"];
    won = j["won"];
    lost = j["lost"];
}


