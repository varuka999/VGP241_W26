#pragma once
#include <iostream>
#include "Enums.h"
#include "Array.h"

class Player
{
public:
    Player();
    Player(int index);
    ~Player();

    void InitializeStats(int index);
    void DisplayStats() const;
    int GetStat(Stats stat) const;
    std::string GetName() const;

private:
    std::string mName = "";
    Array<int, 5> mStatsArray = (0);
};