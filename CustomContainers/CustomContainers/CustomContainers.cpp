#include <iostream>
#include "Array.h"
#include "Vector.h"

int main()
{
    std::cout << "Custom Containers!\n";

    //Array<int, 5> intArray(0);

    //for (std::size_t i = 0; i < intArray.Size(); ++i)
    //{
    //    intArray[i] = i + 1;
    //}

    //for (std::size_t i = 0; i < intArray.Size(); ++i)
    //{
    //    std::cout << "Value at " << i << " = " << intArray[i] << "\n";
    //}

    Vector<int> intVector;
    intVector.Reserve(10);
    for (std::size_t i = 0; i < 10; ++i)
    {
        intVector.PushBack(i + 1);
    }

    std::cout << "Vector\n";
    std::cout << "Vector Size: " << intVector.Size() << "\n";
    std::cout << "Vector Capacity: " << intVector.Capacity() << "\n";
    for (size_t i = 0; i < intVector.Size(); ++i)
    {
        std::cout << "Value at " << i << " = " << intVector[i] << "\n";
    }

    intVector.Resize(5);
    std::cout << "\nVector Resize\n";
    std::cout << "Vector Size: " << intVector.Size() << "\n";
    std::cout << "Vector Capacity: " << intVector.Capacity() << "\n";
    for (size_t i = 0; i < intVector.Size(); ++i)
    {
        std::cout << "Value at " << i << " = " << intVector[i] << "\n";
    }

    for (size_t i = 0; i < 20; ++i)
    {
        intVector.PushBack(i + 10);
    }
    std::cout << "\nVector Plus Ultra\n";
    std::cout << "Vector Size: " << intVector.Size() << "\n";
    std::cout << "Vector Capacity: " << intVector.Capacity() << "\n";
    for (size_t i = 0; i < intVector.Size(); ++i)
    {
        std::cout << "Value at " << i << " = " << intVector[i] << "\n";
    }
}