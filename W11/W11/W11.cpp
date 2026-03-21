#include <iostream>
#include <vector>

void InsertionSort(std::vector<int>& array)
{
	for (int i = 1; i < array.size(); i++)
	{
		int key = array[i];
		int j = i - 1;

		while (j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j--;
		}

		array[j + 1] = key;
	}
}

void Merge(std::vector<int>& array, int left, int mid, int right)
{
	std::vector<int> temp;

	int i = left;
	int j = mid + 1;

	while (i <= mid && j <= right)
	{
		if (array[i] < array[j])
		{
			temp.push_back(array[i++]);
		}
		else
		{
			temp.push_back(array[j++]);
		}
	}

	while (i <= mid)
	{
		temp.push_back(array[i++]);
	}
	while (j <= right)
	{
		temp.push_back(array[j++]);
	}

	for (int k = 0; k < temp.size(); k++)
	{
		array[left + k] = temp[k];
	}
}

void MergeSort(std::vector<int>& arr, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) / 2;

	MergeSort(arr, left, mid);
	MergeSort(arr, mid + 1, right);
	Merge(arr, left, mid, right);
}

int main()
{
	srand(time(NULL));
	std::vector<int> data;

	for (int i = 0; i < 100; i++)
	{
		data.push_back((i * 37) % 1000 + 1);
	}

	std::vector<int> a = data;
	std::vector<int> b = data;

	InsertionSort(a);
	MergeSort(b, 0, b.size() - 1);

	for (int i = 0; i < 10; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < 10; i++)
	{
		std::cout << b[i] << " ";
	}

	return 0;
}