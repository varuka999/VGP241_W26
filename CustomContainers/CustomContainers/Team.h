#pragma once

#include "PlayerA6.h"
#include "Vector.h"
#include "Globals.h"

class Team
{
public:
	void Initialize(int teamNum, int numPlayers)
	{
		for (int i = 0; i < numPlayers; ++i)
		{
			PlayerA6 player;
			player.Initialize(std::string("t") + std::to_string(teamNum), i);
			mPlayers.PushBack(player);
		}
	}

	PlayerA6* GetNextBattlingPlayer()
	{
		if (GetRemainingPlayers() <= 0)
		{
			return nullptr;
		}

		for (std::size_t i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].GetStat(StatsA6::Health) > 0 && mPlayers[i].GetStat(StatsA6::AttackCount) > 0)
			{
				return &mPlayers[i];
			}
		}

		return nullptr;
	}

	void DamagePlayer(PlayerA6* player)
	{
		if (GetRemainingPlayers() <= 0)
		{
			return;
		}

		int aliveIndex = 0;
		do
		{
			aliveIndex = rand() % mPlayers.Size();
		} while (!mPlayers[aliveIndex].IsAlive());

		int damage = player->GetStat(StatsA6::Attack);
		int newHealth = mPlayers[aliveIndex].GetStat(StatsA6::Health) - damage;
		mPlayers[aliveIndex].SetStat(StatsA6::Health, newHealth);

		std::cout << player->GetName() << "(" << player->GetStat(StatsA6::Speed) << "s) attacked " << mPlayers[aliveIndex].GetName() << 
			"(" << player->GetStat(StatsA6::Speed) << "s) for "<< player->GetStat(StatsA6::Attack) << " damage (" << newHealth << " health remaining)\n";

		if ((rand() % 100) < 25)
		{
			int newStat = mPlayers[aliveIndex].GetStat(StatsA6::Speed) - 10;
			mPlayers[aliveIndex].SetStat(StatsA6::Speed, newStat);
		}

		if ((rand() % 100) < 10)
		{
			int newStat = player->GetStat(StatsA6::Speed) + 5;
			player->SetStat(StatsA6::Speed, newStat);
		}

		player->SetStat(StatsA6::AttackCount, 0);
	}

	int GetRemainingPlayers()
	{
		int remaining = 0;

		for (int i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].GetStat(StatsA6::Health) > 0)
			{
				++remaining;
			}
		}

		return remaining;
	}

	void OrderPlayers()
	{
		std::function<bool(const PlayerA6&, const PlayerA6&)> comp = [](const PlayerA6& a, const PlayerA6& b)
			{
				int tempASpeed = a.GetStat(StatsA6::Speed);
				int tempBSpeed = b.GetStat(StatsA6::Speed);

				if (a.GetStat(StatsA6::Health) <= 0 || a.GetStat(StatsA6::AttackCount) <= 0)
				{
					tempASpeed = 0;
				}
				if (b.GetStat(StatsA6::Health) <= 0 || b.GetStat(StatsA6::AttackCount) <= 0)
				{
					tempBSpeed = 0;
				}

				return tempASpeed > tempBSpeed;
			};

		Globals::IntroSort(mPlayers.Begin(), mPlayers.End(), comp);
	}

	void StartTurn()
	{
		for (int i = 0; i < mPlayers.Size(); ++i)
		{
			if (mPlayers[i].GetStat(StatsA6::Health) > 0)
			{
				mPlayers[i].SetStat(StatsA6::AttackCount, 1);
			}
		}

		OrderPlayers();
	}

private:
	std::string mName;
	Vector<PlayerA6> mPlayers;
};