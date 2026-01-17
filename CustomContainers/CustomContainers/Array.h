#pragma once
#include <cstddef>

template<typename T, std::size_t N>
class Array
{
public:
    Array()
    {
        // Allocate memory for N elements of type T
        // Size required is size of T type objects
        // Times the number of elements N
        mValues = new T[N];
    }

    Array(T initializeValue)
    {
        mValues = new T[N];

        for (std::size_t i = 0; i < N; ++i)
        {
            mValues[i] = initializeValue;
        }
    }

    ~Array()
    {
        if (mValues != nullptr)
        {
            delete[] mValues;
            mValues = nullptr;
        }
    }

    // Deep copy constructor
    // Gets called when Array<int, 5> intArray = otherArray
    Array(const Array& other)
    {
        mValues = new T[N];
        for (std::size_t i = 0; i < N; ++i)
        {
            mValues[i] = other.mValues[i];
        }
    }

    // Move constructor
    // Gets called whehn Array<int, 5> intArray = std::move(otherArray)
    Array(Array&& other)
    {
        mValues = other.mValues;
        other.mValues = nullptr;
    }

    // Deep copy assignment
    // Gets called when intArray = otherArray
    Array& operator=(const Array& other)
    {
        if (mValues != nullptr)
        {
            delete[] mValues;
        }

        mValues = new T[N];
        for (int i = 0; i < N; ++i)
        {
            mValues[i] = other.mValues[i];
        }

        return *this;
    }

    // Move assignment
    // Gets called when intArray = std::move(otherArray)
    Array& operator=(Array&& other)
    {
        if (mValues != nullptr)
        {
            delete[] other.mValues;
        }

        mValues = std::move(other.mValues);
        other.mValues = nullptr;

        return *this;
    }

    const std::size_t Size() const
    {
        return N;
    }

    // Gets the data stored in the array
    T* Data()
    {
        return mValues;
    }

    const T* Data() const
    {
        return mValues;
    }

    // Access operator
    T& operator[](std::size_t index)
    {
        // Note, having a check for out of bounds everytime we traverse through an array might be unnecsessary.
        // Can use assert (static_assert) or try/catch. ex: static_assert(N > 0, "Array must be greater than zero!");

        return mValues[index];
    }

    // Const Access operator
    const T& operator[](std::size_t index) const
    {
        return mValues[index];
    }


private:
    T* mValues = nullptr;
};
