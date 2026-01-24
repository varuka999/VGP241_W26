#pragma once

#include <iostream>

template<typename T>
class PriorityQueue
{
public:
    PriorityQueue() {}
    ~PriorityQueue() {}

    bool Empty() const
    {
        return mValues.Size() == 0;
    }

    const std::size_t Size() const
    {
        return mValues.Size();
    }

    void Push(const T& value)
    {
        mValues.PushBack(value);

        // Sort
        HeapifyUp(Size() - 1);
    }

    T Top() const
    {
        return mValues[0];
    }

    void Pop()
    {
        if (Empty())
        {
            return;
        }

        mValues[0] = mValues[Size() - 1];
        mValues.Resize(Size() - 1);

        // Sort Again
        HeapifyDown(0);
    }

private:
    void Swap(T& value1, T& value2)
    { 
        T temp = value1; 
        value1 = value2; 
        value2 = temp; 
    }

    // Maintain MaxHeap property (add)
    void HeapifyUp(int index)
    {
        int parent = (index - 1) / 2;

        while (index > 0 && mValues[index] > mValues[parent])
        {
            Swap(mValues[index], mValues[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    // Maintain MinxHeap property (remove)
    void HeapifyDown(int index)
    {
        int largest = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        if (leftChild < Size() && mValues[leftChild] > mValues[largest])
        {
            largest = leftChild;
        }
        if (rightChild < Size() && mValues[rightChild] > mValues[largest])
        {
            largest = rightChild;
        }
        if (largest != index)
        {
            Swap(mValues[index], mValues[largest]);
            HeapifyDown(largest);
        }
    }

    Vector<T> mValues;
};