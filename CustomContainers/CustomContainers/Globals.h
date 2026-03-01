#pragma once

#include <string>
#include <functional>
#include "Vector.h"

namespace Globals
{
    std::size_t HashFunction(const std::string& str)
    {
        std::size_t hash = 0;
        for (size_t i = 0; i < str.size(); ++i)
        {
            hash = (~hash << 1) + (std::size_t)(str[i]);  //previous alt version: hash = hash << 1; //hash = hash + (std::size_t)(str[i]); OR hash = (hash << 1) + ~((std::size_t)(str[i])); is longer hash;
        }
        return hash;
    }

    template<typename T>
    void Swap(T& a, T& b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template<typename T>
    void BubbleSort(Vector<T>& values)
    {
        std::size_t size = values.Size();
        for (std::size_t i = 0; i < size; ++i)
        {
            for (std::size_t j = 0; j < size - i - 1; ++j)
            {
                if (values[j] > values[j + 1])
                {
                    Swap(values[j], values[j + 1]);
                }
            }
        }
    }
    template<typename T>
    void BubbleSort(Vector<T>& values, std::function<bool(const T&, const T&)>& sortFunc)
    {
        std::size_t size = values.Size();
        for (std::size_t i = 0; i < size; ++i)
        {
            for (std::size_t j = 0; j < size - i - 1; ++j)
            {
                if (sortFunc(values[j], values[j + 1]))
                {
                    Swap(values[j], values[j + 1]);
                }
            }
        }
    }
    template<typename T>
    void SelectionSort(Vector<T>& values)
    {
        std::size_t size = values.Size();
        for (std::size_t i = 0; i < size - 1; ++i)
        {
            std::size_t minIndex = i;
            for (size_t j = i + 1; j < size; ++j)
            {
                if (values[j] < values[minIndex])
                {
                    minIndex = j;
                }
            }
            if (i != minIndex)
            {
                Swap(values[i], values[minIndex]);
            }
        }
    }
    template<typename T>
    void SelectionSort(Vector<T>& values, std::function<bool(const T&, const T&)>& sortFunc)
    {
        std::size_t size = values.Size();
        for (std::size_t i = 0; i < size - 1; ++i)
        {
            std::size_t minIndex = i;
            for (size_t j = i + 1; j < size; ++j)
            {
                if (sortFunc(values[j], values[minIndex]))
                {
                    minIndex = j;
                }
            }
            if (i != minIndex)
            {
                Swap(values[i], values[minIndex]);
            }
        }
    }

    template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
    void InsertionSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
    {
        if (begin == end)
        {
            return;
        }
        for (ContainerIterator<T> iter = begin + 1; iter != end; ++iter)
        {
            T key = *iter;
            ContainerIterator<T> j = iter;
            while (j > begin)
            {
                if (comp(key, *(j - 1)))
                {
                    *j = *(j - 1);
                    --j;
                }
                else
                {
                    break;
                }
                *j = key;
            }
        }
    }
    // a way to hide helper functions for Merge Sort
    namespace MergeSortHelpers
    {
        template<typename T, typename Compare>
        void Merge(ContainerIterator<T> left, ContainerIterator<T> mid, ContainerIterator<T> right, Compare comp)
        {
            // create temp version of each side
            Vector<T> temp;
            temp.Reserve(right - left);
            ContainerIterator<T> tempLeft = left;
            ContainerIterator<T> tempRight = mid;
            while (tempLeft != mid && tempRight != right)
            {
                if (comp(*tempLeft, *tempRight))
                {
                    temp.PushBack(*tempLeft);
                    ++tempLeft;
                    // temp.PushBack(tempLeft++) // nifty, takes the value then after this line will apply the ++
                }
                else
                {
                    temp.PushBack(*tempRight);
                    ++tempRight;
                }
            }
            while (tempLeft != mid)
            {
                temp.PushBack(*tempLeft);
                ++tempLeft;
            }
            while (tempRight != right)
            {
                temp.PushBack(*tempRight);
                ++tempRight;
            }
            for (std::size_t i = 0; i < temp.Size(); ++i)
            {
                *(left + i) = temp[i];
            }
        }

        template<typename T, typename Compare>
        void MergeSortUtil(ContainerIterator<T> begin, ContainerIterator<T> end, std::size_t size, Compare comp)
        {
            if (size > 1)
            {
                std::size_t half = size / 2;
                ContainerIterator<T> mid = begin + half;
                // split the data
                MergeSortUtil(begin, mid, half, comp);
                MergeSortUtil(mid, end, size - half, comp);
                // merge the results
                Merge(begin, mid, end, comp);
            }
        }
    }
    template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
    void MergeSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
    {
        std::size_t size = end - begin;
        MergeSortHelpers::MergeSortUtil(begin, end, size, comp);
    }
    // these are helpers for QuickSort
    namespace QuickSortHelpers
    {
        template<typename T, typename Compare>
        ContainerIterator<T> Partition(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp)
        {
            ContainerIterator<T> pivot = end - 1;
            ContainerIterator<T> i = begin;
            for (ContainerIterator<T> j = begin; j != pivot; ++j)
            {
                if (comp(*j, *pivot))
                {
                    Swap(*i, *j);
                    ++i;
                }
            }
            Swap(*i, *pivot);
            return i;
        }
    }
    template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
    void QuickSprt(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
    {
        if (begin < end && (end - begin) > 1)
        {
            ContainerIterator<T> p = QuickSortHelpers::Partition(begin, end, comp);
            QuickSort(begin, p, comp);
            QuickSort(p + 1, end, comp);
        }
    }

    // can only sort lowest to highest that can be compared
    template<typename T>
    void BucketSort(ContainerIterator<T> begin, ContainerIterator<T> end)
    {
        ContainerIterator<T> maxValue = begin;
        for (ContainerIterator<T> iter = begin; iter != end; ++iter)
        {
            if (*maxValue < *iter)
            {
                maxValue = iter;
            }
        }

        std::size_t size = (end - begin);
        Vector<Vector<T>> buckets;
        buckets.Resize(size);
        for (ContainerIterator<T> iter = begin; iter != end; ++iter)
        {
            std::size_t bucketIndex = ((size - 1) * (*iter)) / (*maxValue);
            buckets[bucketIndex].PushBack(*iter);
        }
        // sort each bucket
        for (std::size_t i = 0; i < size; ++i)
        {
            InsertionSort(buckets[i].Begin(), buckets[i].End());
        }

        // combine all the buckets
        ContainerIterator<T> iter = begin;
        for (std::size_t i = 0; i < size; ++i)
        {
            for (std::size_t j = 0; j < buckets[i].Size(); ++j)
            {
                (*iter) = buckets[i][j];
                ++iter;
            }
        }
    }
    // helper function for heap sort
    namespace HeapSortHelpers
    {
        template<typename T, typename Compare>
        void Heapify(ContainerIterator<T> begin, ContainerIterator<T> root, std::size_t count, Compare comp = Compare())
        {
            ContainerIterator<T> largest = root;
            ContainerIterator<T> i = begin + (2 * (root - begin) + 1);
            ContainerIterator<T> j = begin + (2 * (root - begin) + 2);

            // make sure the value is within container, then compare
            if (i < begin + count && comp(*largest, *i))
            {
                largest = i;
            }
            if (j < begin + count && comp(*largest, *j))
            {
                largest = j;
            }
            if (largest != root)
            {
                Swap(*root, *largest);
                Heapify(begin, largest, count, comp);
            }
        }
    }
    template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
    void HeapSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
    {
        int count = (end - begin) + 1;
        if (count <= 1)
        {
            return;
        }

        // Build the max heap
        for (ContainerIterator<T> i = begin + (count / 2) - 1; i >= begin; --i)
        {
            HeapSortHelpers::Heapify(begin, i, count, comp);
            if (i == begin)
            {
                break;
            }
        }
        // extract the elements from the heap
        for (ContainerIterator<T> i = end; i > begin; --i)
        {
            Swap(*begin, *i);
            HeapSortHelpers::Heapify(begin, begin, i - begin, comp);
        }
    }
    // helper functions for intro sort
    namespace IntroSortHelpers
    {
        template<typename T, typename Compare>
        void IntroSortUtil(ContainerIterator<T> begin, ContainerIterator<T> end, int depthLimit, Compare comp = Compare())
        {
            // if less than 16 elements, use insertion sort
            std::size_t count = end - begin;
            if (count < 16)
            {
                InsertionSort(begin, end, comp);
                return;
            }

            // if depth limit is reached due to recursion, use heap sort
            if (depthLimit <= 0)
            {
                HeapSort(begin, end, comp);
                return;
            }

            // function as if it is quick sort
            ContainerIterator<T> p = QuickSortHelpers::Partition(begin, end, comp);
            IntroSortUtil(begin, p, depthLimit - 1, comp);
            IntroSortUtil(p, end, depthLimit - 1, comp);
        }
    }
    template<typename T, typename Compare = std::less<typename std::iterator_traits<ContainerIterator<T>>::value_type>>
    void IntroSort(ContainerIterator<T> begin, ContainerIterator<T> end, Compare comp = Compare())
    {
        std::size_t count = (end - begin);
        if (end - begin > 1)
        {
            int depthLimit = 2 * std::log2(count);
            IntroSortHelpers::IntroSortUtil(begin, end, depthLimit, comp);
        }
    }
}