#include <iostream>
#include "Array.h"
#include "Vector.h"
#include "Player.h"
#include "PriorityQueue.h"
#include "Inventory.h"
#include "Globals.h"
#include "UnorderedMap.h"
#include "Entity.h"
#include "InventoryA5.h"
#include "Team.h"

void ClassPractice()
{
	std::cout << "Custom Containers!\n";

	Array<int, 5> intArray(0);

	//for (std::size_t i = 0; i < intArray.Size(); ++i)
	//{
	//    intArray[i] = i + 1;
	//}

	//for (std::size_t i = 0; i < intArray.Size(); ++i)
	//{
	//    std::cout << "Value at " << i << " = " << intArray[i] << "\n";
	//}

	Vector<int> intVector;
	intVector.Reserve(10);
	for (std::size_t i = 0; i < 10; ++i)
	{
		intVector.PushBack(i + 1);
	}

	std::cout << "Vector\n";
	std::cout << "Vector Size: " << intVector.Size() << "\n";
	std::cout << "Vector Capacity: " << intVector.Capacity() << "\n";
	for (size_t i = 0; i < intVector.Size(); ++i)
	{
		std::cout << "Value at " << i << " = " << intVector[i] << "\n";
	}

	intVector.Resize(5);
	std::cout << "\nVector Resize\n";
	std::cout << "Vector Size: " << intVector.Size() << "\n";
	std::cout << "Vector Capacity: " << intVector.Capacity() << "\n";
	for (size_t i = 0; i < intVector.Size(); ++i)
	{
		std::cout << "Value at " << i << " = " << intVector[i] << "\n";
	}

	for (size_t i = 0; i < 20; ++i)
	{
		intVector.PushBack(i + 10);
	}
	std::cout << "\nVector Plus Ultra\n";
	std::cout << "Vector Size: " << intVector.Size() << "\n";
	std::cout << "Vector Capacity: " << intVector.Capacity() << "\n";
	for (size_t i = 0; i < intVector.Size(); ++i)
	{
		std::cout << "Value at " << i << " = " << intVector[i] << "\n";
	}
}

void ClassPractice2()
{
	Array<int, 10> myInts;
	for (int i = 0; i < myInts.Size(); ++i)
	{
		myInts[i] = rand() % 100;
	}

	for (Array<int, 10>::Iterator iter = myInts.Begin(); iter != myInts.End(); ++iter)
	{
		std::cout << "Array Value: " << *iter << "\n";
	}

	std::sort(myInts.Begin(), myInts.End());
	std::cout << "\nSorted\n";
	for (Array<int, 10>::Iterator iter = myInts.Begin(); iter != myInts.End(); ++iter)
	{
		std::cout << "Array Value: " << *iter << "\n";
	}

	PriorityQueue<int> priorityQueue;
	for (int i = 0; i < 20; ++i)
	{
		int value = rand() % 100;
		priorityQueue.Push(value);
		std::cout << value << " ";
	}
	std::cout << "\n\n";
	while (!priorityQueue.Empty())
	{
		std::cout << priorityQueue.Top() << " ";
		priorityQueue.Pop();
	}
}

void Assignment1()
{
	Vector<Player> playersVector;
	playersVector.Reserve(10);

	for (size_t i = 0; i < 10; ++i)
	{
		playersVector.PushBack(Player(i + 1));
	}

	std::cout << "Added 10 Players!\n\n";

	for (size_t i = 0; i < playersVector.Size(); ++i)
	{
		playersVector[i].DisplayStats();
	}

	playersVector.Resize(4);
	std::cout << "Removed 6 Players!\n\n";

	while (playersVector.Size() < 20)
	{
		playersVector.PushBack(Player(playersVector.Size() + 1));
	}
	std::cout << "Added up to 20 Players!\n\n";

	for (size_t i = 0; i < playersVector.Size(); ++i)
	{
		playersVector[i].DisplayStats();
	}

	int combatPlayer1 = rand() % playersVector.Size();
	int combatPlayer2 = 0;
	do
	{
		combatPlayer2 = rand() % playersVector.Size();
	} while (combatPlayer2 == combatPlayer1);

	std::cout << playersVector[combatPlayer1].GetName() << " & " << playersVector[combatPlayer2].GetName() << " are fighting!\n";

	//Calculations
	float p1 = (float)((playersVector[combatPlayer1].GetStat(Stats::Attack) * playersVector[combatPlayer1].GetStat(Stamina)) - (playersVector[combatPlayer2].GetStat(Stats::Defense) * playersVector[combatPlayer2].GetStat(Stats::Speed)))
		/ (float)playersVector[combatPlayer2].GetStat(Stats::Health);
	float p2 = (float)((playersVector[combatPlayer2].GetStat(Stats::Attack) * playersVector[combatPlayer2].GetStat(Stamina)) - (playersVector[combatPlayer1].GetStat(Stats::Defense) * playersVector[combatPlayer1].GetStat(Stats::Speed)))
		/ (float)playersVector[combatPlayer1].GetStat(Stats::Health);

	//p1 = 1.0f; //Quick test to see tiebreaker if it doesn't happen naturally.
	//p2 = 1.0f;

	int winnerID = -1;

	if (p1 > p2)
	{
		winnerID = combatPlayer1;
	}
	else if (p2 > p1)
	{
		winnerID = combatPlayer2;
	}
	else // Tie
	{
		std::cout << "(TIE BREAKER)\n";
		winnerID = rand() % 2 == 0 ? combatPlayer1 : combatPlayer2;
	}

	std::cout << playersVector[winnerID].GetName() << " won!\n";
}

void Assignment2()
{
	Inventory inventory;
	std::cout << "Creating Default Inventory!\n\n";
	inventory.Initialize();
	inventory.DisplayInventory();

	std::cout << "\nAdding 100 Random Items!\n\n";
	for (int i = 0; i < 100; i++)
	{
		int randItemEnum = rand() % ItemType::Count;
		inventory.AddItem((static_cast<ItemType>(randItemEnum)));
	}

	std::cout << "\nSuccessfully Updated Inventory!\n";
	inventory.DisplayInventory();
}

void Assignment4()
{
	Vector<Entity> myEntities;

	Entity player1;
	Entity player2;
	player1.Initialize("Player1Texture.png");
	player2.Initialize("Player2Texture.png");
	myEntities.PushBack(player1);
	myEntities.PushBack(player2);

	std::function<bool(const Entity&, const Entity&)> sortFunc = [](const Entity& a, const Entity& b)
		{
			return a.DistanceSqrToOrigin() > b.DistanceSqrToOrigin();
		};

	for (int i = 0; i < 20; ++i)
	{
		Entity enemy;
		enemy.Initialize("EnemyTexture.png");
		myEntities.PushBack(enemy);
	}

	std::cout << "Unsorted Render:\n";
	for (size_t i = 0; i < myEntities.Size(); ++i)
	{
		myEntities[i].Render();
	}

	std::cout << "\n";

	for (int a = 0; a < 3; ++a)
	{
		std::cout << "Render " << a + 1 << ":\n";

		for (size_t i = 0; i < myEntities.Size(); ++i)
		{
			myEntities[i].Update();
		}

		Globals::BubbleSort(myEntities, sortFunc);

		for (size_t i = 0; i < myEntities.Size(); ++i)
		{
			myEntities[i].Render();
		}

		std::cout << "\n";
	}

}

void Assignment5()
{
	int unlockedDoors = 0;
	int failedAttempts = 0;
	bool running = true;

	Vector<std::string> mKeyNames;
	for (int i = 0; i < 20; ++i)
	{
		mKeyNames.PushBack(std::string("Key") + std::to_string(i + 1));
	}

	for (int i = 0; i < 100; ++i)
	{
		int randomNameIndex = rand() % mKeyNames.Size();
		InventoryA5::Get()->AddKey(mKeyNames[randomNameIndex], 1);
	}

	Vector<std::string> mMyKeys;
	InventoryA5::Get()->ObtainKeyNames(mMyKeys);

	for (std::size_t i = 0; i < mMyKeys.Size(); ++i)
	{
		std::cout << mMyKeys[i] << "\n";
	}

	while (running)
	{
		std::cout << "\nPress Enter to continue...\n";
		std::cin.get();

		std::cout << "Choose an option:\n";
		std::cout << "1. Open Door\n";
		std::cout << "2. Pick Up Key\n";
		std::cout << "3. Exit\n";

		int input = 0;
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (input == 1)
		{
			int randomIndex = rand() % mKeyNames.Size();
			std::string requiredKey = mKeyNames[randomIndex];

			std::cout << "You arrive at a door and need a " << requiredKey << "\n";

			KeyItem item;
			if (InventoryA5::Get()->HasKey(requiredKey))
			{
				std::cout << "You have the " << requiredKey << " and have unlocked the door\n";

				InventoryA5::Get()->UseKey(requiredKey, 1);
				++unlockedDoors;
			}
			else
			{
				std::cout << "You do not have the " << requiredKey << ", the door will remain locked\n";
				++failedAttempts;
			}
		}
		else if (input == 2)
		{
			int randomIndex = rand() % mKeyNames.Size();
			std::string pickedKey = mKeyNames[randomIndex];

			InventoryA5::Get()->AddKey(pickedKey, 1);

			KeyItem item;
			InventoryA5::Get()->GetKey(pickedKey, item);

			std::cout << "Picked up: " << pickedKey << " (Total: " << item.GetCount() << ")\n";
		}
		else if (input == 3)
		{
			running = false;
		}
	}

	std::cout << "\nInventory\n";

	Vector<std::string> ownedKeys;
	InventoryA5::Get()->ObtainKeyNames(ownedKeys);

	for (std::size_t i = 0; i < ownedKeys.Size(); ++i)
	{
		KeyItem item;
		if (InventoryA5::Get()->GetKey(ownedKeys[i], item))
		{
			std::cout << ownedKeys[i] << ": " << item.GetCount() << "\n";
		}
	}

	std::cout << "Total doors unlocked: " << unlockedDoors << "\n";
	std::cout << "Failed unlock attempts: " << failedAttempts << "\n";
}

void Assignment6()
{
	Team team1;
	Team team2;

	team1.Initialize(1, 10);
	team2.Initialize(2, 10);

	int round = 1;

	while (team1.GetRemainingPlayers() > 0 && team2.GetRemainingPlayers() > 0)
	{
		std::cout << "\nRound " << round << "\n";

		team1.StartTurn();
		team2.StartTurn();

		while (true)
		{
			PlayerA6* player1 = team1.GetNextBattlingPlayer();
			PlayerA6* player2 = team2.GetNextBattlingPlayer();

			if (player1 == nullptr && player2 == nullptr)
			{
				break;
			}

			if (player2 == nullptr && player1 != nullptr) // incase one team dies early
			{
				team2.DamagePlayer(player1);
			}
			else if (player1 == nullptr && player2 != nullptr)
			{
				team1.DamagePlayer(player2);
			}
			else
			{
				int player1Speed = player1->GetStat(StatsA6::Speed);
				int player2Speed = player2->GetStat(StatsA6::Speed);

				if (player1Speed >= player2Speed)
				{
					team2.DamagePlayer(player1);
				}
				else
				{
					team1.DamagePlayer(player2);
				}
			}

			team1.OrderPlayers();
			team2.OrderPlayers();

			if (team1.GetRemainingPlayers() <= 0 || team2.GetRemainingPlayers() <= 0)
			{
				break;
			}
		}

		std::cout << "Team1 remaining players: " << team1.GetRemainingPlayers() << "\n";
		std::cout << "Team2 remaining players: " << team2.GetRemainingPlayers() << "\n";

		++round;
	}

	if (team1.GetRemainingPlayers() > 0)
	{
		std::cout << "\nTeam 1 Wins!!\n";
	}
	else
	{
		std::cout << "\nTeam 2 Wins!!\n";
	}
}

void Week6()
{
	UnorderedMap<std::string, int> myCarPrices;
	myCarPrices.Insert("Ford", 10000);
	myCarPrices.Insert("Chevy", 25000);
	myCarPrices["Dodge"] = 30000;
	myCarPrices["BMW"] = 100000;

	std::cout << "Price of Ford " << myCarPrices["Ford"] << "\n";
	std::cout << "Price of Chevy " << myCarPrices["Chevy"] << "\n";
	std::cout << "Price of Dodge " << myCarPrices["Dodge"] << "\n";
	std::cout << "Price of BMW " << myCarPrices["BMW"] << "\n";
	std::cout << "Number of cars" << myCarPrices.GetCount() << "\n";
	myCarPrices.Remove("Ford");

	std::cout << "HashValues\n";
	std::cout << "RAT: " << Globals::HashFunction("RAT") << "\n";
	std::cout << "TAR: " << Globals::HashFunction("TAR") << "\n";
	std::cout << "Ford: " << Globals::HashFunction("Ford") << "\n";
	std::cout << "Chevy: " << Globals::HashFunction("Chevy") << "\n";
	std::cout << "Dodge: " << Globals::HashFunction("Dodge") << "\n";
	std::cout << "BMW: " << Globals::HashFunction("BMW") << "\n";
}

void Week8()
{
	Vector<int> myNumbers;
	int maxNumbers = 20;
	for (int i = 0; i < maxNumbers; ++i)
	{
		int value = 1 + (rand() % 1000);
		myNumbers.PushBack(value);
		std::cout << value << " ";
	}
	std::cout << "\n";

	Globals::IntroSort(myNumbers.Begin(), myNumbers.End());
	for (int i = 0; i < myNumbers.Size(); ++i)
	{
		std::cout << myNumbers[i] << " ";
	}
	std::cout << "\n";
}

int main()
{
	srand(time(NULL));

	//Assignment1();
	//Assignment2();
	//Assignment4();
	//Assignment5();
	Assignment6();
}