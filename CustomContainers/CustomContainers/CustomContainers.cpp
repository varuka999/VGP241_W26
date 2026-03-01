#include <iostream>
#include "Array.h"
#include "Vector.h"
#include "Player.h"
#include "PriorityQueue.h"
#include "Inventory.h"
#include "Globals.h"
#include "UnorderedMap.h"

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
    float p1 = (float)((playersVector[combatPlayer1].GetStat(Attack) * playersVector[combatPlayer1].GetStat(Stamina)) - (playersVector[combatPlayer2].GetStat(Defense) * playersVector[combatPlayer2].GetStat(Speed)))
        / (float)playersVector[combatPlayer2].GetStat(Health);
    float p2 = (float)((playersVector[combatPlayer2].GetStat(Attack) * playersVector[combatPlayer2].GetStat(Stamina)) - (playersVector[combatPlayer1].GetStat(Defense) * playersVector[combatPlayer1].GetStat(Speed)))
        / (float)playersVector[combatPlayer1].GetStat(Health);

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

int main()
{
    srand(time(NULL));

    //Assignment1();
    //Assignment2();

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