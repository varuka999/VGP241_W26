


#include <iostream>
#include <array>
#include <vector>
#include <string>
//const int MAX_HASH_SIZE = 20;
//int HashFunction(int key)
//{
//	return key % MAX_HASH_SIZE;
//}
//struct Node
//{
//	int key;
//	int data;
//	Node* next;
//};
//std::array<Node*, MAX_HASH_SIZE> hashTable = { nullptr };
//void Insert(int key, int data)
//{
//	int index = HashFunction(key);
//	Node* tmp = hashTable[index];
//	while (tmp != nullptr)
//	{
//		if (tmp->key == key)
//		{
//			std::cout << "Key " << key << " is already added!\n";
//			return;
//		}
//		tmp = tmp->next;
//	}
//	Node* newNode = new Node();
//	newNode->key = key;
//	newNode->data = data;
//	newNode->next = hashTable[index];
//	hashTable[index] = newNode;
//	std::cout << "Inserted " << key << " : " << data << " : " << index << "\n";
//}
//int Search(int key)
//{
//	int index = HashFunction(key);
//	Node* foundNode = hashTable[index];
//	while (foundNode != nullptr)
//	{
//		if (foundNode->key == key)
//		{
//			return foundNode->data;
//		}
//		foundNode = foundNode->next;
//	}
//	return -1;
//}
//void Delete(int key)
//{
//	int index = HashFunction(key);
//	Node* node = hashTable[index];
//	Node* prev = nullptr;
//	while (node != nullptr)
//	{
//		if (node->key == key)
//		{
//			if (prev != nullptr)
//			{
//				prev->next = node->next;
//			}
//			else
//			{
//				hashTable[index] = node->next;
//			}
//			delete node;
//			node = nullptr;
//			break;
//		}
//		prev = node;
//		node = node->next;
//	}
//}
//void Print()
//{
//	std::cout << "Printing Hash Table Size: " << MAX_HASH_SIZE << "\n";
//	for (int i = 0; i < MAX_HASH_SIZE; ++i)
//	{
//		if (hashTable[i] != nullptr)
//		{
//			Node* node = hashTable[i];
//			while (node != nullptr)
//			{
//				std::cout << node->data << " index (" << i << ")\n";
//				node = node->next;
//			}
//		}
//	}
//}
//int Exercise1PracticeHashTable()
//{
//	srand(time(NULL));
//	std::cout << "Working with Hash Tables and Sorting\n";
//	Insert(1, rand() % 100);
//	Insert(2, rand() % 100);
//	Insert(4, rand() % 100);
//	Insert(15, rand() % 100);
//	Insert(22, rand() % 100);
//	Insert(30, rand() % 100);
//	Insert(36, rand() % 100);
//	Print();
//
//	Delete(2);
//
//	Print();
//}










class Texture
{
public:
	Texture() : mPixelColors(nullptr) {}
	~Texture()
	{
		if (mPixelColors != nullptr)
		{
			delete[] mPixelColors;
			mPixelColors = nullptr;
		}
	}
	void Intialize(const std::string& filePath, int size)
	{
		mFilePath = filePath;
		mPixelColors = new float[size * size * 4];
	}
	const std::string& GetFilePath() const
	{
		return mFilePath;
	}

private:
	std::string mFilePath = "";
	float* mPixelColors = nullptr;
};

struct Node
{
	Texture* data;
	Node* next;
};
const int MAX_HASH_SIZE = 1000;
std::array<Node*, MAX_HASH_SIZE> HashTable = { nullptr };
int HashFunction(const std::string& key)
{
	int hashValue = 0;
	for (int i = 0; i < key.size(); ++i)
	{
		int value = (int)key[i];
		hashValue = (hashValue * 256 + value) % MAX_HASH_SIZE;
	}
	return hashValue % MAX_HASH_SIZE;
}
void InsertTextire(const std::string& filePath)
{
	int index = HashFunction(filePath);
	Node* tmp = HashTable[index];
	while (tmp != nullptr)
	{
		if (tmp->data->GetFilePath() == filePath)
		{
			std::cout << "Texture " << filePath << " is already added!\n";
			return;
		}
		tmp = tmp->next;
	}
	Texture* newTexture = new Texture();
	newTexture->Intialize(filePath, 100 + (rand() % 157));
	Node* newNode = new Node();
	newNode->data = newTexture;
	newNode->next = HashTable[index];
	HashTable[index] = newNode;
}

const Texture* FindTexture(const std::string& filePath)
{
	int index = HashFunction(filePath);
	Node* foundNode = HashTable[index];
	while (foundNode != nullptr)
	{
		if (foundNode->data->GetFilePath() == filePath)
		{
			return foundNode->data;
		}
		foundNode = foundNode->next;
	}
	return nullptr;
}
void DeleteTexture(const std::string& filePath)
{
	int index = HashFunction(filePath);
	Node* node = HashTable[index];
	Node* prev = nullptr;
	while (node != nullptr)
	{
		if (node->data->GetFilePath() == filePath)
		{
			if (prev != nullptr)
			{
				prev->next = node->next;
			}
			else
			{
				HashTable[index] = node->next;
			}
			std::cout << "Texture " << filePath << " was deleted\n";
			delete node->data;
			node->data = nullptr;
			delete node;
			node = nullptr;
			break;
		}
		prev = node;
		node = node->next;
	}
}
void Print()
{
	for (int i = 0; i < MAX_HASH_SIZE; ++i)
	{
		Node* node = HashTable[i];
		while (node != nullptr)
		{
			std::cout << i << ") " << node->data->GetFilePath() << "\n";
			node = node->next;
		}
	}
}

std::vector<std::string> directories{
	"/Models/Textures/",
	"/UI/Textures/",
	"/Gameplay/Textures/",
	"/Environment/Textures/"
};
int main()
{
	int maxTextures = 100;
	for (int i = 0; i < maxTextures; ++i)
	{
		int dirIndex = rand() % directories.size();
		std::string fullPath = directories[dirIndex] + "TextureName_" + std::to_string(i);
		InsertTextire(fullPath);
	}
	Print();

	std::cout << "===============================================\n";
	std::cout << "===============================================\n";
	std::string findTexture = "TextureName_" + std::to_string(rand() % 100);
	std::cout << "Find Texture " << findTexture << "\n";
	const Texture* texture = FindTexture(findTexture);
	if (texture != nullptr)
	{
		std::cout << "Texture " << texture->GetFilePath() << " was found!\n";
	}
	else
	{
		std::cout << "Texture " << findTexture << " was not found!!!\n";
	}
	std::cout << "===============================================\n";
	std::cout << "===============================================\n";
	std::cout << "===============================================\n";
	for (int i = 0; i < maxTextures; ++i)
	{
		DeleteTexture("TextureName_" + std::to_string(rand() % 100));
	}
	Print();
}