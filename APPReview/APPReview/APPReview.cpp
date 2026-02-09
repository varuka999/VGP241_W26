// APPReview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <string>
#include <stack>

int O1()
{
	return 3 * 3;
}

int On(int n)
{
	int sumTotal = 0;

	for (int i = 0; i < n; i++)
	{
		sumTotal += 3;
	}

	return sumTotal;
}

int logn(int n)
{
	int sumTotal = 0;

	for (int i = 1; i < n; i *= 3)
	{
		sumTotal += 3;
	}

	return sumTotal;
}

void PrintRecursive(const std::vector<int>& nums, int index)
{
	if (index < 0)
	{
		return;
	}

	PrintRecursive(nums, index - 1);
	std::cout << nums[index] << "\n";
}

void PrintRecursive2(const std::vector<int>& nums, int index)
{
	std::cout << nums[index] << "\n";

	if (index >= nums.size() - 1)
	{
		return;
	}

	PrintRecursive2(nums, ++index);
}

class House
{
public:
	int price = 0;
	int squareFoot = 0;
	int rooms = 0;
	int distance = 0;

	bool operator()(const House& a, const House& b)
	{
		return a.price < b.price;
	}
};

struct SortByPrice
{
	bool operator()(const House& a, const House& b)
	{
		return a.price < b.price;
	}
};

struct SortBySqrFoot
{
	bool operator()(const House& a, const House& b)
	{
		return a.squareFoot < b.squareFoot;
	}
};

struct SortByDistance
{
	bool operator()(const House& a, const House& b)
	{
		return a.distance < b.distance;
	}
};

struct SortByRoom
{
	bool operator()(const House& a, const House& b)
	{
		if (a.rooms == b.rooms)
		{
			return a.price < b.price;
		}
		return a.rooms < b.rooms;
	}
};

class HouseListing
{
public:
	void AddHouse(const House& house)
	{
		mHouses.push_back(house);
	}

	template<typename Callback>
	void PrintWithCriteria()
	{
		std::priority_queue<House, std::vector<House>, Callback> sortedHouses;

		for (int i = 0; i < mHouses.size(); ++i)
		{
			sortedHouses.push(mHouses[i]);
		}

		while (!sortedHouses.empty())
		{
			House top = sortedHouses.top();
			sortedHouses.pop();
			std::cout << "Price " << top.price << " ";
			std::cout << "Rooms " << top.rooms << " ";
			std::cout << "Distance " << top.distance << " ";
			std::cout << "SqrFoot " << top.squareFoot << "\n";
		}
	}

private:
	std::vector<House> mHouses;
};

void PriorityQueueExercise()
{
	HouseListing houseListings;
	for (int i = 0; i < 20; ++i)
	{
		House newHouse;
		newHouse.distance = 10 + (rand() % 100);
		newHouse.rooms = 2 + (rand() % 8);
		newHouse.squareFoot = newHouse.rooms * (100 + (rand() % 50));
		newHouse.price = newHouse.squareFoot * (1000 + (rand() % 50)) / (newHouse.distance / 2);
		houseListings.AddHouse(newHouse);
	}

	houseListings.PrintWithCriteria<SortByPrice>();
}

struct Node
{
	// data for display
	std::string data;
	bool visited = false;
	// to obtain path, need to keep track of where we came from
	const Node* fromNode = nullptr;
	// connected nodes, can be any number of connections
	std::vector<Node*> edges;
};

class Graph
{
public:
	void CreateGraph(int width, int height)
	{
		// creates all the nodes
		mNodes.resize(width * height);

		for (int h = 0; h < height; ++h)
		{
			for (int w = 0;  w < width;  ++w)
			{
				int index = w + (h * width);
				if (w + 1 < width)
				{
					int right = (w + 1) + (h * width);
					mNodes[index].edges.push_back(&mNodes[right]);
					mNodes[right].edges.push_back(&mNodes[index]);
				}
				if (h + 1 < height)
				{
					int down = w + ((h + 1) * height);
					mNodes[index].edges.push_back(&mNodes[down]);
					mNodes[down].edges.push_back(&mNodes[index]);
				}

				mNodes[index].data = std::to_string(w) + "_" + std::to_string(h);

			}
		}
	}

	void PrintPathDFS(int startIndex, int endIndex)
	{
		Reset();
		std::cout << "Printing Path (DFS):\n";
		std::vector<bool> visited;
		visited.resize(mNodes.size(), false);

		Node* startNode = &mNodes[startIndex];
		Node* endNode = &mNodes[endIndex];
		std::stack<Node*> stack;
		stack.push(startNode);
		while (!stack.empty())
		{
			Node* node = stack.top();
			stack.pop();
			if (!node->visited)
			{
				node->visited = true;
				if (node == endNode)
				{
					break;
				}
				for (int i = 0; i < node->edges.size(); ++i)
				{
					Node* edgeNode = node->edges[i];
					if (!edgeNode->visited)
					{
						edgeNode->fromNode = node;
						stack.push(edgeNode);
					}
				}
			}
		}

		const Node* path = endNode;
		while (path != nullptr)
		{
			std::cout << path->data << " ";
			path = path->fromNode;
		}
	}
	
	void PrintPathBFS(int startIndex, int endIndex)
	{
		Reset();
		std::cout << "Printing Path (BFS):\n";
		std::vector<bool> visited;
		visited.resize(mNodes.size(), false);
		Node* startNode = &mNodes[startIndex];
		Node* endNode = &mNodes[endIndex];
		std::queue<Node*> queue;
		queue.push(startNode);
		while (!queue.empty())
		{
			Node* node = queue.front();
			queue.pop();
			if (!node->visited)
			{
				node->visited = true;
				if (node == endNode)
				{
					break;
				}
				for (int i = 0; i < node->edges.size(); ++i)
				{
					Node* edgeNode = node->edges[i];
					if (!edgeNode->visited)
					{
						edgeNode->fromNode = node;
						queue.push(edgeNode);
					}
				}
			}
		}
		const Node* path = endNode;
		while (path != nullptr)
		{
			std::cout << path->data << " ";
			path = path->fromNode;
		}
	}

	void Reset()
	{
		for (int i = 0; i < mNodes.size(); ++i)
		{
			mNodes[i].visited = false;
			mNodes[i].fromNode = nullptr;
		}
	}

private:
	std::vector<Node> mNodes;
};

void GraphExercise()
{
	int width = 0;
	int height = 0;
	std::cout << "Enter width";
	std::cin >> width;
	std::cout << "Enter height";
	std::cin >> height;

	Graph graph;
	graph.CreateGraph(width, height);
	int startIndex = 0;
	int endIndex = 0;
	std::cout << "Enter start index";
	std::cin >> startIndex;
	std::cout << "Enter end index";
	std::cin >> endIndex;
	graph.PrintPathDFS(startIndex, endIndex);
	std::cout << "\n";
	graph.PrintPathBFS(startIndex, endIndex);
}


int main()
{
	//std::vector<int> nums;

	//for (int i = 0; i < 100; i++)
	//{
	//	nums.push_back(i);
	//}

	//PrintRecursive(nums, nums.size() - 1);
	//PrintRecursive2(nums, 0);

	//PriorityQueueExercise();
	GraphExercise();
}

// Create a function that has a time complexity of
// O(1) Constant
// O(n) Linear
// O(logn) Logorithmic