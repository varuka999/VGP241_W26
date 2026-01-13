#include "Player.h"
#include <string>

Player::Player()
{
}

Player::Player(int index)
{
    InitializeStats(index);
}

Player::~Player()
{
}

void Player::InitializeStats(int index)
{
    mName = "player" + std::to_string(index);

    mStatsArray[Health] = 100;
    for (size_t i = Attack; i <= Speed; i++)
    {
        int randomNum = 1 + rand() % 5;
        mStatsArray[i] = randomNum;
    }
}

void Player::DisplayStats() const
{
    std::cout << mName << " Stats:\n";
    for (int i = 0; i < mStatsArray.Size(); i++)
    {
        std::cout << mStatsArray[i] << "\n";
    }
    std::cout << "\n";
}

int Player::GetStat(Stats stat) const
{
    return mStatsArray[stat];
}

std::string Player::GetName() const
{
    return mName;
}
