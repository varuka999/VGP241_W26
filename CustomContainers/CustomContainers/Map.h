#pragma once
#include <iostream>
#include <algorithm>
#include "Vector.h"

template<typename KeyType, typename ValueType>
class Map
{
public:
	struct KeyValuePair
	{
		KeyType key;
		ValueType value;
	};
	struct Node
	{
		KeyValuePair kvp;
		Node* left = nullptr;
		Node* right = nullptr;
		int height = 0;
	};

public:
	Map() {}
	~Map()
	{
		Clear();
	}
	void Insert(const KeyType& key, const ValueType& value)
	{
		KeyValuePair kv;
		kv.key = key;
		kv.value = value;
		mRootNode = InsertNode(mRootNode, kv);
	}
	bool Find(const KeyType& key, ValueType& outValue) const
	{
		Node* node = FindNode(mRootNode, key);
		if (node != nullptr)
		{
			outValue = node->kvp.value;
		}
		return node != nullptr;
	}
	bool Has(const KeyType& key) const
	{
		return FindNode(mRootNode, key) != nullptr;
	}
	void ObtainKeys(Vector<KeyType>& outKeys) const
	{
		ObtainKeysFromNodes(mRootNode, outKeys);
	}
	bool Remove(const KeyType& key)
	{
		int count = mCount;
		mRootNode = DeleteNode(mRootNode, key);
		return mCount < count;
	}
	std::size_t Count() const
	{
		return mCount;
	}
	void Clear()
	{
		mRootNode = DeleteAllNodes(mRootNode);
		mCount = 0;
	}
	ValueType& operator[](const KeyType& key)
	{
		Node* node = FindNode(mRootNode, key);
		if (node == nullptr)
		{
			Insert(key, mDefaultValue);
			node = FindNode(mRootNode, key);
		}
		return node->kvp.value;
	}
	const ValueType& operator[](const KeyType& key) const
	{
		Node* node = FindNode(mRootNode, key);
		if (node != nullptr)
		{
			return node->kvp.value;
		}
		return mDefaultValue;
	}
private:
	ValueType mDefaultValue;
	std::size_t mCount = 0;
	Node* mRootNode = nullptr;

	int NodeHeight(Node* node)
	{
		if (node != nullptr)
		{
			return node->height;
		}
		return 0;
	}
	int GetBalanceFactor(Node* node)
	{
		if (node != nullptr)
		{
			return NodeHeight(node->left) - NodeHeight(node->right);
		}
		return 0;
	}
	Node* RotateRight(Node* y)
	{
		Node* x = y->left;
		Node* temp = x->right;
		x->right = y;
		y->left = temp;
		y->height = std::max(NodeHeight(y->left), NodeHeight(y->right)) + 1;
		x->height = std::max(NodeHeight(x->left), NodeHeight(x->right)) + 1;
		return x;
	}
	Node* RotateLeft(Node* x)
	{
		Node* y = x->right;
		Node* temp = y->left;
		y->left = x;
		x->right = temp;
		x->height = std::max(NodeHeight(x->left), NodeHeight(x->right)) + 1;
		y->height = std::max(NodeHeight(y->left), NodeHeight(y->right)) + 1;
		return y;
	}
	Node* InsertNode(Node* node, KeyValuePair& kv)
	{
		if (node == nullptr)
		{
			Node* node = new Node();
			node->kvp = std::move(kv);
			node->left = nullptr;
			node->right = nullptr;
			node->height = 0;
			++mCount;
			return node;
		}
		if (kv.key < node->kvp.key)
		{
			node->left = InsertNode(node->left, kv);
		}
		else if (kv.key > node->kvp.key)
		{
			node->right = InsertNode(node->right, kv);
		}
		else
		{
			// can put an assert
			// all keys should be unique
			return node;
		}

		node->height = std::max(NodeHeight(node->left), NodeHeight(node->right)) + 1;
		int balance = GetBalanceFactor(node);
		if (balance > 1 && kv.key < node->left->kvp.key)
		{
			return RotateRight(node);
		}
		if (balance < -1 && kv.key > node->right->kvp.key)
		{
			return RotateLeft(node);
		}
		if (balance > 1 && kv.key > node->left->kvp.key)
		{
			node->left = RotateLeft(node->left);
			return RotateRight(node);
		}
		if (balance < -1 && kv.key < node->right->kvp.key)
		{
			node->right = RotateRight(node->right);
			return RotateLeft(node);
		}
		return node;
	}
	Node* FindNode(Node* node, const KeyType& key) const
	{
		if (node == nullptr)
		{
			return node;
		}
		if (node->kvp.key == key)
		{
			return node;
		}
		if (key < node->kvp.key)
		{
			return FindNode(node->left, key);
		}
		return FindNode(node->right, key);
	}
	Node* DeleteNode(Node* node, const KeyType& key)
	{
		if (node == nullptr)
		{
			return node;
		}
		if (key < node->kvp.key)
		{
			node->left = DeleteNode(node->left, key);
		}
		else if (key > node->kvp.key)
		{
			node->right = DeleteNode(node->right, key);
		}
		else
		{
			if (node->left == nullptr)
			{
				Node* temp = node->right;
				delete node;
				node = nullptr;
				--mCount;
				return temp;
			}
			if (node->right == nullptr)
			{
				Node* temp = node->left;
				delete node;
				node = nullptr;
				--mCount;
				return temp;
			}
			Node* temp = node->right;
			while (temp != nullptr && temp->left != nullptr)
			{
				temp = temp->left;
			}
			node->kvp = temp->kvp;
			node->right = DeleteNode(node->right, temp->kvp.key);
			node->height = std::max(NodeHeight(node->left), NodeHeight(node->right)) + 1;

			int balance = GetBalanceFactor(node);
			if (balance > 1 && GetBalanceFactor(node->left) >= 0)
			{
				return RotateRight(node);
			}
			if (balance < -1 && GetBalanceFactor(node->right) <= 0)
			{
				return RotateLeft(node);
			}
			if (balance > 1 && GetBalanceFactor(node->left) < 0)
			{
				node->left = RotateLeft(node->left);
				return RotateRight(node);
			}
			if (balance < -1 && GetBalanceFactor(node->right) > 0)
			{
				node->right = RotateLeft(node->right);
				return RotateLeft(node);
			}
		}
		return node;
	}

	void ObtainKeysFromNodes(Node* node, Vector<KeyType>& outKeys) const
	{
		if (node != nullptr)
		{
			ObtainKeysFromNodes(node->left, outKeys);
			outKeys.PushBack(node->kvp.key);
			ObtainKeysFromNodes(node->right, outKeys);
		}
	}

	Node* DeleteAllNodes(Node* node)
	{
		if (node != nullptr)
		{
			node->left = DeleteAllNodes(node->left);
			node->right = DeleteAllNodes(node->right);
			delete node;
			node = nullptr;
		}
		return node;
	}
};