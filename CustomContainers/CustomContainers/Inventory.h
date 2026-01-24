#pragma once
#include "Item.h"
#include "Vector.h"
#include "PriorityQueue.h"
#include <iostream>

class Inventory
{
public:
	Inventory() {}
	~Inventory() {}
	void Initialize()
	{
		AddItem(SmallPotion);
		AddItem(SmallPotion);
		AddItem(SmallPotion);
		AddItem(SmallPotion);
		AddItem(SmallPotion);
		AddItem(MediumPotion);
		AddItem(MediumPotion);
		AddItem(MediumPotion);
		AddItem(LargePotion);
		AddItem(LargePotion);
		AddItem(FireBall);
		AddItem(FireBall);
		AddItem(IceBall);
		AddItem(ThunderBall);
		AddItem(ThunderBall);
		AddItem(WaterBall);
		AddItem(WaterBall);
		AddItem(WaterBall);
		AddItem(WaterBall);
		AddItem(WaterBall);
	}

	// Go through list to see if item already exists
	void AddItem(ItemType itemType)
	{
		for (std::size_t i = 0; i < mItems.Size(); ++i)
		{
			if (mItems[i].GetType() == itemType)
			{
				mItems[i].AddItem();
				return;
			}
		}

		int randValue = rand() % 50;
		mItems.PushBack(Item(itemType, randValue));
	}
	void DisplayInventory() const
	{
		std::cout << "\nInventory:\n";

		PriorityQueue<Item> tempPriorityQueue;
		for (std::size_t i = 0; i < mItems.Size(); ++i)
		{
			tempPriorityQueue.Push(mItems[i]);
		}

		int inventorySize = 0;

		while (!tempPriorityQueue.Empty())
		{
			Item top = tempPriorityQueue.Top();
			inventorySize += top.GetCount();
			std::cout << top.GetName() << " Count: " << top.GetCount() << "\n";
			tempPriorityQueue.Pop();
		}

		std::cout << "Total Inventory Size: " << inventorySize << "\n";
	}
private:
	Vector<Item> mItems;
};