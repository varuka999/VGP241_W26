#pragma once
#include "Enums.h"
#include <iostream>
//#include <string>

class Item
{
public:
	Item()
		: mType(Null), mName("Null"), mValue(0), mCount(0)
	{
	}
	Item(ItemType type, int value)
		: mType(type), mValue(value), mCount(0)
	{
		switch (mType)
		{
		case SmallPotion:
			mName = "Small Potion";
			break;
		case MediumPotion:
			mName = "Medium Potion";
			break;
		case LargePotion:
			mName = "Large Potion";
			break;
		case FireBall:
			mName = "Fire Ball";
			break;
		case IceBall:
			mName = "Ice Ball";
			break;
		case ThunderBall:
			mName = "Thunder Ball";
			break;
		case WaterBall:
			mName = "Water Ball";
			break;
		default:
			mName = "Null";
			break;
		}

		AddItem();
	}

	bool operator>(const Item& other) const
	{
		if (mCount != other.mCount)
		{
			return mCount > other.mCount;
		}

		return mName < other.mName; // I wanted lowercase items to be higher priority, swap < -> > if I wanted uppercase to be higher priority
	}
	bool operator<(const Item& other) const
	{
		if (mCount != other.mCount)
		{
			return mCount < other.mCount;
		}

		return mName < other.mName;
	}

	void Consume()
	{
		if (mCount > 0)
		{
			--mCount;
			std::cout << "Consumed a " << mName << " (Remaining: " << mCount << ")\n";
		}
		else
		{
			std::cout << "No " << mName << " left to consume!\n";
		}
	}

	void AddItem()
	{
		++mCount;
		std::cout << "Added a " << mName << " (Total: " << mCount << ")\n";
	}

	ItemType GetType() const { return mType; }
	const std::string& GetName() const { return mName; }
	int GetCount() const { return mCount; }

private:
	ItemType mType;
	std::string mName;
	int mValue;
	int mCount;
};