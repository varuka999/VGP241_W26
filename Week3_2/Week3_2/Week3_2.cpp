// Week3Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

struct Node
{
    int mData = 0;
    Node* mChild = nullptr;
};
Node* AddToList(Node* parent, int value)
{
    Node* newNode = new Node();
    newNode->mData = value;
    if (parent != nullptr)
    {
        parent->mChild = newNode;
    }
    return newNode;
}
void DeleteList(Node* node)
{
    if (node != nullptr)
    {
        DeleteList(node->mChild);
        delete node;
        node = nullptr;
    }
}
bool LinkedListIsCyclical(Node* root)
{
    //  Bonus:?
    //  Randomly link a node to a child and a parent(as long as it doesnot
    //      already have one)?
    //      How can you test to see if the linked list has any cyclical loops ?
    Node* slowNode = root;
    Node* fastNode = root;
    while (slowNode != nullptr && fastNode != nullptr && fastNode->mChild != nullptr)
    {
        slowNode = slowNode->mChild;
        fastNode = fastNode->mChild->mChild;
        if (slowNode == fastNode)
        {
            return true;
        }
    }

    return false;
}
void Exercise1LinkedList()
{
    //  Create a simple linked list?
    //  Node?
    //      Data?
    //      Child?
    //  Create a couple dozen nodes?
    //  How many elements do you have to search to find the target ?

    Node* prevNode = nullptr;
    Node* root = nullptr;
    for (int i = 0; i < 300; ++i)
    {
        prevNode = AddToList(prevNode, (rand() % 100) + 1);
        if (root == nullptr)
        {
            root = prevNode;
        }
    }

    std::cout << "List of numbers:\n";
    if (!LinkedListIsCyclical(root))
    {
        Node* tmp = root;
        while (tmp != nullptr)
        {
            std::cout << tmp->mData << "\n";
            tmp = tmp->mChild;
        }
        DeleteList(root);
    }
    else
    {
        std::cout << "Linked List Is Cyclical!!!\n";
    }
}

struct Vector2
{
    int x = 0;
    int y = 0;
};
struct KDNode
{
    Vector2 mData;
    KDNode* mLeft = nullptr;
    KDNode* mRight = nullptr;
};
KDNode* Insert(const Vector2& v, KDNode* prev, int k)
{
    if (prev == nullptr)
    {
        KDNode* newNode = new KDNode();
        newNode->mData = v;
        return newNode;
    }

    if (prev->mData.x == v.x && prev->mData.y == v.y)
    {
        std::cout << "[ERROR] Node Already Added!!!\n";
        return prev;
    }
    // we are looking at the first dimension which is x
    if (k == 0)
    {
        // k % 2 because it is 2 dimensions, x and y, so k will then be y 
        if (v.x < prev->mData.x)
        {
            prev->mLeft = Insert(v, prev->mLeft, (k + 1) % 2);
        }
        else
        {
            prev->mRight = Insert(v, prev->mRight, (k + 1) % 2);
        }
    }
    // we are looking at the second dimension which is y
    else if (k == 1)
    {
        if (v.y < prev->mData.y)
        {
            prev->mLeft = Insert(v, prev->mLeft, (k + 1) % 2);
        }
        else
        {
            prev->mRight = Insert(v, prev->mRight, (k + 1) % 2);
        }
    }
    // should not be here, may need to make more dynamic or prevent more than 2 dimensions
    else
    {
        std::cout << "[ERROR] dimension not set up\n";
    }
    return prev;
}
// prints at a tree level
void PrintDataAtLevel(KDNode* node, int level, const std::string& side)
{
    if (node == nullptr)
    {
        return;
    }
    if (level == 0)
    {
        std::cout << side << " (" << node->mData.x << ", " << node->mData.y << ") ";
    }
    else
    {
        PrintDataAtLevel(node->mLeft, level - 1, "L");
        PrintDataAtLevel(node->mRight, level - 1, "R");
        if (level == 1)
        {
            std::cout << "  ";
        }
    }
}

// prints the tree
void PrintTree(KDNode* tree)
{
    std::cout << "\n\n\nPrinting Tree:\n";
    for (int i = 0; i < 20; ++i)
    {
        PrintDataAtLevel(tree, i, "ROOT");
        std::cout << "\n";
    }
}

void DeleteKDTree(KDNode* node)
{
    if (node != nullptr)
    {
        DeleteKDTree(node->mLeft);
        DeleteKDTree(node->mRight);
        delete node;
        node = nullptr;
    }
}

int main()
{
    std::cout << "Hello World!\n";

    Vector2 v;
    KDNode* root = nullptr;
    for (int i = 0; i < 20; ++i)
    {
        v.x = rand() % 101;
        v.y = rand() % 101;
        KDNode* newNode = Insert(v, root, 0);
        if (root == nullptr)
        {
            root = newNode;
        }
        std::cout << "(" << v.x << ", " << v.y << ")\n";
    }

    DeleteKDTree(root);
}