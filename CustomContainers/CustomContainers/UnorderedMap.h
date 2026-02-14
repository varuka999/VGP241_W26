#pragma once

#include <vector>
#include <functional>

template<typename KeyType, typename ValueType>
class UnorderedMap
{
private:
    struct KeyValuePair
    {
        KeyType key;
        ValueType value;
    };
public:
    UnorderedMap(std::size_t initialBucketSize = 8, double loadFactor = 0.75)
        : mLoadFactorThreshold(loadFactor)
        , mCount(0)
    {
        // in case we set it to 0
        mBucketCount = std::max<std::size_t>(initialBucketSize, 1);
        mTable.resize(mBucketCount);
    }
    // delete copy and move constructors
    // prevents duplicating dating losing content
    UnorderedMap(const UnorderedMap&) = delete;
    UnorderedMap(const UnorderedMap&&) = delete;
    UnorderedMap& operator=(const UnorderedMap&) = delete;
    UnorderedMap& operator=(const UnorderedMap&&) = delete;

    void Insert(const KeyType& key, const ValueType& value)
    {
        std::size_t index = GetTableIndex(key);

        // check if we already have the key
        for (KeyValuePair* kv : mTable[index])
        {
            if (kv->key == key)
            {
                // if so update the value and return
                kv->value = value;
                return;
            }
        }

        // otherwise add the new key and value
        KeyValuePair* kv = new KeyValuePair();
        kv->key = key;
        kv->value = value;
        mTable[index].push_back(kv);
        ++mCount;

        if ((double)mCount / (double)mBucketCount > mLoadFactorThreshold)
        {
            Rehash();
        }
    }

    bool Find(const KeyType& key, ValueType& outValue) const
    {
        std::size_t index = GetTableIndex(key);
        for (const KeyValuePair* kv : mTable[index])
        {
            if (kv->key == key)
            {
                outValue = kv->value;
                return true;
            }
        }
        return false;
    }
    bool Has(const KeyType& key)
    {
        std::size_t index = GetTableIndex(key);
        for (const KeyValuePair* kv : mTable[index])
        {
            if (kv->key == key)
            {
                return true;
            }
        }
        return false;
    }

    bool Remove(const KeyType& key)
    {
        std::size_t index = GetTableIndex(key);
        std::vector<KeyValuePair*>& bucket = mTable[index];
        for (auto iter = bucket.begin(); iter != bucket.end(); ++iter)
        {
            if ((*iter)->key == key)
            {
                delete (*iter);
                (*iter) = nullptr;
                bucket.erase(iter);
                --mCount;
                return true;
            }
        }
        return false;
    }

    std::size_t GetCount() const
    {
        return mCount;
    }

    void Clear()
    {
        for (std::vector<KeyValuePair*>& bucket : mTable)
        {
            for (KeyValuePair* kv : bucket)
            {
                delete kv;
                kv = nullptr;
            }
            bucket.clear();
        }
        mTable.clear();
        mCount = 0;
    }

    // data accessors
    ValueType& operator[](const KeyType& key)
    {
        std::size_t index = GetTableIndex(key);
        for (KeyValuePair* kv : mTable[index])
        {
            if (kv->key == key)
            {
                return kv->value;
            }
        }
        KeyValuePair* kv = new KeyValuePair();
        kv->key = key;
        kv->value = mDefault;
        mTable[index].push_back(kv);
        ++mCount;
        return kv->value;     // lets us do mMyMap["Vancouver"] = cool; instead of mMyMap.insert("Vancouver", cool)
    }

    const ValueType& operator[](const KeyType& key) const
    {
        std::size_t index = GetTableIndex(key);
        for (const KeyValuePair* kv : mTable[index])
        {
            if (kv->key == key)
            {
                return kv->value;
            }
        }

        return mDefault;
    }

private:
    ValueType mDefault;
    // Table is main vector, "Bucket" is vector of object using same index
    std::vector<std::vector<KeyValuePair*>> mTable;
    // max indeces the table can use to store individual values
    std::size_t mBucketCount = 0;
    // number of items in the table
    std::size_t mCount = 0;
    // how many items in a bucket before we need to resize
    double mLoadFactorThreshold = 1.0;
    // dynamic hash function, gives a hash value from whatever we use as a key
    std::hash<KeyType> mHashFunction;

    // gives the index in the table that the item will be placed
    // due to the hash value obtained with the key
    std::size_t GetTableIndex(const KeyType& key) const
    {
        return mHashFunction(key) % mBucketCount;
    }

    void Rehash()
    {
        std::size_t newBucketCount = mBucketCount * 2;
        std::vector<std::vector<KeyValuePair*>> newTable;
        newTable.resize(newBucketCount);
        
        // set it first so we can reuse "GetTableINdex"
        mBucketCount = newBucketCount;
        for (std::vector<KeyValuePair*>& bucket : mTable)
        {
            for (KeyValuePair* kv : bucket)
            {
                std::size_t index = GetTableIndex(kv->key);
                newTable[index].push_back(kv);
            }
            bucket.clear();
        }
        mTable.clear();
        // swap the new table to the old table
        mTable.swap(newTable);
    }
};