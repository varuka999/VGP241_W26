#include <iostream>
#include <cmath>
#include <iomanip>
#include "Array.h"
#include "Vector.h"
#include "Player.h"
#include "PriorityQueue.h"
#include "Inventory.h"
#include "Globals.h"
#include "UnorderedMap.h"
#include "Entity.h"
#include "InventoryA5.h"
#include "MSTGraph.h"
#include "MSTGraphK.h"
#include "Team.h"
#include "WeightedGraph.h"

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

#pragma region Assignment7
#pragma region Functions
struct HousePosition
{
    float x = 0.0f;
    float y = 0.0f;
};
class House
{
public:
    House()
    {
    }

    House(const std::string& name, float x, float y)
        : mName(name)
    {
        mPosition.x = x;
        mPosition.y = y;
    }

    std::string mName = "";
    HousePosition mPosition;
};
class City
{
public:
    void AddHouse(const std::string& name, float x, float y)
    {
        House newHouse = House(name, x, y);
        mHouses.PushBack(newHouse);
    }
    void BuildRoad()
    {
        mPrimGraph.Terminate();
        mKruskalGraph.Clear();
        mKruskalGraph.SetNodeCount(mHouses.Size());

        for (std::size_t i = 0; i < mHouses.Size(); ++i)
        {
            mPrimGraph.AddItem(&mHouses[i]);
        }

        for (int i = 0; i < mHouses.Size(); ++i)
        {
            for (int j = i + 1; j < mHouses.Size(); ++j)
            {
                float distance = GetDistance(mHouses[i], mHouses[j]);

                mPrimGraph.AddEdge(i, j, distance, true);
                mKruskalGraph.AddEdge(i, j, distance);
            }
        }
    }
    float GetTotalRoadDistancePrim(int startNode = 0)
    {
        float totalDistance = 0.0f;

        mPrimGraph.GenerateMST(startNode);
        const Vector<MSTGraph<House, float>::Edge>& mst = mPrimGraph.GetMST();
        for (std::size_t i = 0; i < mst.Size(); ++i)
        {
            totalDistance += mst[i].weight;
        }

        return totalDistance;
    }

    float GetTotalRoadDistanceKruskal()
    {
        float totalDistance = 0.0f;

        mKruskalGraph.GenerateMST();

        const Vector<MSTGraphK<float>::Edge>& mst = mKruskalGraph.GetMST();

        for (std::size_t i = 0; i < mst.Size(); ++i)
        {
            totalDistance += mst[i].weight;
        }

        return totalDistance;
    }

    void PrintPrimMST(int startNode = 0)
    {
        mPrimGraph.GenerateMST(startNode);

        const Vector<MSTGraph<House, float>::Edge>& mst = mPrimGraph.GetMST();

        float totalDistance = 0.0f;

        std::cout << "Prim MST:\n";

        for (std::size_t i = 0; i < mst.Size(); ++i)
        {
            const auto& edge = mst[i];
            std::cout << mHouses[edge.fromIndex].mName << "-" << mHouses[edge.toIndex].mName << " : " << std::fixed << std::setprecision(2) << edge.weight << " meters\n";
            totalDistance += edge.weight;
        }

        std::cout << "Total Distance: " << totalDistance << " meters\n";
        std::cout << "Total Cost: $" << (totalDistance * 10.0f) << "\n\n";
    }

    void PrintKruskalMST()
    {
        mKruskalGraph.GenerateMST();

        const Vector<MSTGraphK<float>::Edge>& mst = mKruskalGraph.GetMST();

        float totalDistance = 0.0f;

        std::cout << "Kruskal MST:\n";

        for (std::size_t i = 0; i < mst.Size(); ++i)
        {
            const auto& edge = mst[i];
            std::cout << mHouses[edge.fromNode].mName << "-" << mHouses[edge.toNode].mName << " : " << std::fixed << std::setprecision(2) << edge.weight << " meters\n";
            totalDistance += edge.weight;
        }

        std::cout << "Total Distance: " << totalDistance << " meters\n";
        std::cout << "Total Cost: $" << (totalDistance * 10.0f) << "\n\n";
    }
private:
    float GetDistance(const House& a, const House& b)
    {
        float dx = b.mPosition.x - a.mPosition.x;
        float dy = b.mPosition.y - a.mPosition.y;

        return std::sqrt((dx * dx) + (dy * dy));
    }

private:
    Vector<House> mHouses;
    MSTGraph<House, float> mPrimGraph;
    MSTGraphK<float> mKruskalGraph;
};
#pragma endregion

void Assignment7()
{
    City city;
    city.AddHouse("A", 20.0f, 40.0f);
    city.AddHouse("B", 50.0f, 20.0f);
    city.AddHouse("C", 90.0f, 40.0f);
    city.AddHouse("D", 60.0f, 80.0f);
    city.AddHouse("E", 30.0f, 120.0f);
    city.AddHouse("F", 100.0f, 110.0f);
    city.AddHouse("G", 150.0f, 130.0f);
    city.AddHouse("H", 160.0f, 90.0f);
    city.AddHouse("I", 140.0f, 60.0f);
    city.AddHouse("J", 180.0f, 30.0f);
    city.AddHouse("K", 200.0f, 120.0f);
    city.AddHouse("L", 220.0f, 70.0f);
    city.AddHouse("M", 240.0f, 50.0f);
    city.BuildRoad();
    city.PrintPrimMST(0);
    city.PrintKruskalMST();
    float primDistance = city.GetTotalRoadDistancePrim(0);
    float kruskalDstance = city.GetTotalRoadDistanceKruskal();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Prim Total Road Distance: " << primDistance << " meters\n";
    std::cout << "Prim Total Road Cost: $" << (primDistance * 10.0f) << "\n";
    std::cout << "Kruskal Total Road Distance: " << kruskalDstance << " meters\n";
    std::cout << "Kruskal Total Road Cost: $" << (kruskalDstance * 10.0f) << "\n";
}
#pragma endregion

#pragma region Assignment8
#pragma region Functions
class City2
{
public:
    City2()
    {

    }
    City2(const std::string& name, const Vector2& position)
        : mName(name), mPosition(position)
    {

    }

    std::string mName = "";
    Vector2 mPosition;
};
class GPS
{
public:
    void AddCity(const std::string& name, const Vector2& pos)
    {
        if (FindCityIndexByName(name) != -1)
        {
            return;
        }

        for (std::size_t i = 0; i < mCities.Size(); ++i)
        {
            if (mCities[i].mPosition.x == pos.x && mCities[i].mPosition.y == pos.y)
            {
                return;
            }
        }

        City2 city = City2(name, pos);
        mCities.PushBack(city);
    }
    void BuildGraph()
    {
        mCityGraph.Terminate();

        for (std::size_t i = 0; i < mCities.Size(); ++i)
        {
            mCityGraph.AddItem(&mCities[i]);
        }
    }
    void ConnectCities(const City2& a, const City2& b)
    {
        int indexA = FindCityIndex(a);
        int indexB = FindCityIndex(b);

        if (indexA == -1 || indexB == -1)
        {
            return;
        }

        float distance = GetDistance(a, b);
        mCityGraph.AddEdge(indexA, indexB, distance);
    }
    float FindPath(const City2& from, const City2& to, Vector<const City2*>& pathOutput)
    {
        int startIndex = FindCityIndex(from);
        int endIndex = FindCityIndex(to);

        if (startIndex == -1 || endIndex == -1)
        {
            pathOutput.Clear();
            return -1.0f;
        }

        Vector<const City2*> reversedPath = {};
        float totalDistance = mCityGraph.GetPath(startIndex, endIndex, reversedPath);

        pathOutput.Clear();

        for (int i = static_cast<int>(reversedPath.Size()) - 1; i >= 0; --i)
        {
            pathOutput.PushBack(reversedPath[i]);
        }

        return totalDistance;
    }
    const City2* GetCity(const std::string& name) const
    {
        for (std::size_t i = 0; i < mCities.Size(); ++i)
        {
            if (mCities[i].mName == name)
            {
                return &mCities[i];
            }
        }

        return nullptr;
    }
private:
    int FindCityIndex(const City2& city) const
    {
        for (std::size_t i = 0; i < mCities.Size(); ++i)
        {
            if (mCities[i].mName == city.mName)
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }
    int FindCityIndexByName(const std::string& name) const
    {
        for (std::size_t i = 0; i < mCities.Size(); ++i)
        {
            if (mCities[i].mName == name)
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }
    float GetDistance(const City2& a, const City2& b) const
    {
        float dx = b.mPosition.x - a.mPosition.x;
        float dy = b.mPosition.y - a.mPosition.y;
        return std::sqrt((dx * dx) + (dy * dy));
    }

public:
    Vector<City2> mCities;
    WeightedGraph<City2, float> mCityGraph;
};

void PrintRoute(GPS& gps, const std::string& fromName, const std::string& toName)
{
    const City2* fromCity = gps.GetCity(fromName);
    const City2* toCity = gps.GetCity(toName);

    if (fromCity == nullptr || toCity == nullptr)
    {
        return;
    }

    Vector<const City2*> pathOutput;
    float distance = gps.FindPath(*fromCity, *toCity, pathOutput);

    std::cout << "Path From: " << fromName << " to " << toName;
    for (std::size_t i = 0; i < pathOutput.Size(); ++i)
    {
        std::cout << pathOutput[i]->mName;

        if (i < pathOutput.Size() - 1)
        {
            std::cout << "-";
        }
    }

    float hours = distance / 80.0f;
    int wholeHours = static_cast<int>(hours);
    int minutes = static_cast<int>((hours - wholeHours) * 60.0f + 0.5f);

    if (minutes == 60)
    {
        wholeHours += 1;
        minutes = 0;
    }

    std::cout << "\n" << std::fixed << std::setprecision(2);
    std::cout << "Total Distance: " << distance << " km\n";
    std::cout << "Estimated Time: " << wholeHours << "h " << minutes << "m\n\n";
}
#pragma endregion

void Assignment8()
{
    GPS gps;
    gps.AddCity("Powell River", { 420.0f, 605.0f });
    gps.AddCity("Vancouver", { 475.0f, 635.0f });
    gps.AddCity("Abbotsford", { 505.0f, 650.0f });
    gps.AddCity("Penticton", { 600.0f, 615.0f });
    gps.AddCity("Kelowna", { 603.0f, 593.0f });
    gps.AddCity("Kamloops", { 570.0f, 555.0f });
    gps.AddCity("Nelson", { 685.0f, 608.0f });
    gps.AddCity("Creston", { 715.0f, 625.0f });
    gps.AddCity("Cranbrook", { 740.0f, 598.0f });
    gps.AddCity("Revelstoke", { 642.0f, 526.0f });
    gps.AddCity("Lillooet", { 512.0f, 556.0f });
    gps.AddCity("Prince George", { 447.0f, 376.0f });
    gps.AddCity("Burns Lake", { 375.0f, 362.0f });
    gps.AddCity("Smithers", { 330.0f, 330.0f });
    gps.AddCity("Terrace", { 285.0f, 345.0f });
    gps.AddCity("Prince Rupert", { 227.0f, 352.0f });
    gps.AddCity("Dawson Creek", { 550.0f, 268.0f });
    gps.AddCity("Fort St. John", { 530.0f, 243.0f });
    gps.AddCity("Fort Nelson", { 470.0f, 102.0f });
    gps.AddCity("Dease Lake", { 250.0f, 120.0f });
    gps.AddCity("Williams Lake", { 500.0f, 475.0f });
    gps.AddCity("Quesnel", { 485.0f, 430.0f });

    gps.BuildGraph();

    gps.ConnectCities(*gps.GetCity("Prince Rupert"), *gps.GetCity("Terrace"));
    gps.ConnectCities(*gps.GetCity("Terrace"), *gps.GetCity("Smithers"));
    gps.ConnectCities(*gps.GetCity("Smithers"), *gps.GetCity("Burns Lake"));
    gps.ConnectCities(*gps.GetCity("Burns Lake"), *gps.GetCity("Prince George"));
    gps.ConnectCities(*gps.GetCity("Prince George"), *gps.GetCity("Quesnel"));
    gps.ConnectCities(*gps.GetCity("Quesnel"), *gps.GetCity("Williams Lake"));
    gps.ConnectCities(*gps.GetCity("Williams Lake"), *gps.GetCity("Lillooet"));
    gps.ConnectCities(*gps.GetCity("Lillooet"), *gps.GetCity("Kamloops"));
    gps.ConnectCities(*gps.GetCity("Kamloops"), *gps.GetCity("Revelstoke"));
    gps.ConnectCities(*gps.GetCity("Revelstoke"), *gps.GetCity("Cranbrook"));
    gps.ConnectCities(*gps.GetCity("Kamloops"), *gps.GetCity("Penticton"));
    gps.ConnectCities(*gps.GetCity("Penticton"), *gps.GetCity("Kelowna"));
    gps.ConnectCities(*gps.GetCity("Kelowna"), *gps.GetCity("Nelson"));
    gps.ConnectCities(*gps.GetCity("Nelson"), *gps.GetCity("Creston"));
    gps.ConnectCities(*gps.GetCity("Creston"), *gps.GetCity("Cranbrook"));
    gps.ConnectCities(*gps.GetCity("Vancouver"), *gps.GetCity("Powell River"));
    gps.ConnectCities(*gps.GetCity("Vancouver"), *gps.GetCity("Abbotsford"));
    gps.ConnectCities(*gps.GetCity("Abbotsford"), *gps.GetCity("Penticton"));
    gps.ConnectCities(*gps.GetCity("Prince George"), *gps.GetCity("Dawson Creek"));
    gps.ConnectCities(*gps.GetCity("Dawson Creek"), *gps.GetCity("Fort St. John"));
    gps.ConnectCities(*gps.GetCity("Fort St. John"), *gps.GetCity("Fort Nelson"));
    gps.ConnectCities(*gps.GetCity("Fort Nelson"), *gps.GetCity("Dease Lake"));
    gps.ConnectCities(*gps.GetCity("Dease Lake"), *gps.GetCity("Terrace"));

    PrintRoute(gps, "Vancouver", "Cranbrook");
    PrintRoute(gps, "Prince Rupert", "Kelowna");
    PrintRoute(gps, "Fort Nelson", "Creston");
}
#pragma endregion

int main()
{
    srand(time(NULL));

    //Assignment1();
    //Assignment2();
    //Assignment4();
    //Assignment5();
    //Assignment6();
    //Assignment7();
    //Assignment8();
}