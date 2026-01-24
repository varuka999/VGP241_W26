#pragma once

#include <algorithm>
#include <iterator>
#include <cstddef>

template<typename T>
class ContainerIterator
{
public:
    // Define ids/names for stl use (std::sort, std::find, etc)
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

public:
    ContainerIterator(T* ptr) : mPtr(ptr) {}

    T& operator*() const { return *mPtr; }
    T* operator->() const { return mPtr; }

    // ++iter
    ContainerIterator& operator++() { ++mPtr; return *this; }
    // --iter
    ContainerIterator& operator--() { --mPtr; return *this; }
    // iter++
    ContainerIterator& operator++(int) { ContainerIterator tmp = *this; ++(this); return tmp; }
    // iter--
    ContainerIterator& operator--(int) { ContainerIterator tmp = *this; --(this); return tmp; }

    ContainerIterator operator+(difference_type n) const { return ContainerIterator(mPtr + n); }
    ContainerIterator operator-(difference_type n) const { return ContainerIterator(mPtr - n); }
    ContainerIterator& operator+=(difference_type n) const { mPtr += n; return *this; }
    ContainerIterator& operator-=(difference_type n) const { mPtr -= n; return *this; }

    difference_type operator-(const ContainerIterator& other) const { return mPtr - other.mPtr; }

    // Comparisons
	bool operator==(const ContainerIterator& other) const { return mPtr == other.mPtr; }
	bool operator!=(const ContainerIterator& other) const { return mPtr != other.mPtr; }
	bool operator<(const ContainerIterator& other) const { return mPtr < other.mPtr; }
	bool operator>(const ContainerIterator& other) const { return mPtr > other.mPtr; }
	bool operator>=(const ContainerIterator& other) const { return mPtr >= other.mPtr; }
	bool operator<=(const ContainerIterator& other) const { return mPtr <= other.mPtr; }

private:
    T* mPtr;
};