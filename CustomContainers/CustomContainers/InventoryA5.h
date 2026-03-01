#pragma once

#include "Map.h"
#include "KeyItem.h"

class InventoryA5
{
public:
	static InventoryA5* Get()
	{
		static InventoryA5 sInstance;
		return &sInstance;
	}

	void AddKey(const std::string& keyName, int amount)
	{
		KeyItem& keyItem = mKeys[keyName];

		if (keyItem.GetCount() == 0) // If count is 0, key didn't exist
		{
			keyItem.SetName(keyName);
		}

		keyItem.Add(amount);
	}

	void UseKey(const std::string& keyName, int amount)
	{
		KeyItem& keyItem = mKeys[keyName];
		keyItem.Consume(amount);
	}

	void ObtainKeyNames(Vector<std::string>& outKeys) const
	{
		mKeys.ObtainKeys(outKeys);
	}

	bool HasKey(const std::string& keyName) const
	{
		return mKeys.Has(keyName);
	}

	bool GetKey(const std::string& keyName, KeyItem& outItem) const
	{
		return mKeys.Find(keyName, outItem);
	}

private:
	InventoryA5() = default;
	~InventoryA5() = default;

	Map<std::string, KeyItem> mKeys;
};