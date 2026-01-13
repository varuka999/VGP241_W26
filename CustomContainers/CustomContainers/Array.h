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

    // Deep copy constructor ->Review
    Array(const Array& other)
    {
        mValues = new T[N];
        for (std::size_t i = 0; i < N; ++i)
        {
            mValues[i] = other.mValues[i];
        }
    }

    // Deep copy assignment ->Review
    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            T* newValues = new T[N];
            for (std::size_t i = 0; i < N; ++i)
            {
                newValues[i] = other.mValues[i];
            }

            delete[] mValues;
            mValues = newValues;
        }
        return *this;
    }
    // Move constructor ->Review
    Array(Array&& other) noexcept
        : mValues(other.mValues)
    {
        other.mValues = nullptr;
    }

    // Move assignment ->Review
    Array& operator=(Array&& other) noexcept
    {
        if (this != &other)
        {
            delete[] mValues;
            mValues = other.mValues;
            other.mValues = nullptr;
        }
        return *this;
    }

    ~Array()
    {
        delete[] mValues;
        mValues = nullptr;
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