#include <iostream>
#include <array>
#include <vector>
#include <chrono>

std::chrono::steady_clock::time_point gStartTime;
//std::chrono::steady_clock::time_point gEndTime;

void StartAlgorithm()
{
	std::cout << "Algorithm Started\n";
	gStartTime = std::chrono::high_resolution_clock::now();
}

void PrintDuration()
{
	std::chrono::steady_clock::time_point endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - gStartTime).count();
	std::cout << "Duration (ns): " << duration << "\n";
}

void PrintRandomValues(int* array, int maxSize, int maxValues)
{
	for (int i = 0; i < maxValues; ++i)
	{
		int randomIndex = rand() % maxSize;
		int value = array[randomIndex];
		std::cout << "Value at index " << randomIndex << " is " << value << "\n";
	}
}

int GetNumberOfRepeats(const std::vector<int>& vector, int value)
{
	int count = 0;
	for (int i = 0; i < vector.size(); ++i)
	{
		if (vector[i] == value)
		{
			++count;
		}
	}

	return count;
}

void Exercise1()
{
	std::array<int, 100> array1;
	std::array<int, 10000> array2;

	for (int i = 0; i < 100; ++i)
	{
		array1[i] = i;
	}

	for (int i = 0; i < 10000; ++i)
	{
		array2[i] = i;
	}

	StartAlgorithm();
	PrintRandomValues(array1.data(), 100, 20);
	PrintDuration();
	std::cout << "\n";

	StartAlgorithm();
	PrintRandomValues(array2.data(), 10000, 20);
	PrintDuration();
	std::cout << "\n";

	//for (int i = 0; i < 20; ++i)
	//{
	//	int randomIndex = rand() % 100;
	//	int value = array1[randomIndex]
	//}
}

void Exercise2()
{
	std::vector<int> vector1;
	std::vector<int> vector2;
	vector1.resize(100);
	for (int i = 0; i < vector1.size(); ++i)
	{
		vector1[i] = (rand() % 50) + 1;
	}

	vector2.resize(10000);
	for (int i = 0; i < vector2.size(); ++i)
	{
		vector2[i] = (rand() % 50) + 1;
	}

	int inputNumber = 0;
	std::cout << "Enter a num between 1-50: ";
	std::cin >> inputNumber;

	StartAlgorithm();
	int count = GetNumberOfRepeats(vector1, inputNumber);
	std::cout << "Vector 1: " << count << "\n";
	PrintDuration();

	StartAlgorithm();
	count = GetNumberOfRepeats(vector2, inputNumber);
	std::cout << "Vector 2: " << count << "\n";
	PrintDuration();
}

int main()
{

}