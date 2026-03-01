#pragma once

#include <iostream>
#include "Enums.h"

class PlayerA6
{
public:
	void Initialize(std::string team, int index)
	{
		mStats[(int)StatsA6::Health] = 100;
		for (int i = (int)StatsA6::Attack; i < (int)StatsA6::AttackCount; ++i)
		{
			mStats[i] = 5 + rand() % 16;
		}
		mStats[(int)StatsA6::AttackCount] = 1;

		mName = team + std::to_string(index + 1);
	}

	std::string GetName() const
	{
		return mName;
	}

	int GetStat(StatsA6 stat) const
	{
		return mStats[(int)stat];
	}

	void SetStat(StatsA6 stat, int value)
	{
		mStats[(int)stat] = value;
	}

	bool IsAlive() const
	{
		return mStats[(int)StatsA6::Health] > 0;
	}

private:
	std::string mName;
	int mStats[4];
};