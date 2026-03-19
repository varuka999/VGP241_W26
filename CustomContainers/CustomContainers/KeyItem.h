#pragma once

#include <iostream>

class KeyItem
{
public:
	void Add(int amount)
	{
		mCount += amount;
	}
	
	void Consume(int amount)
	{
		mCount -= amount;
	}

	int GetCount() const
	{
		return mCount;
	}

	void SetName(const std::string& keyName)
	{
		mName = keyName;
	}

	void Print()
	{
		std::cout << mName << ": " << mCount;
	}

private:
	std::string mName;
	int mCount;
};