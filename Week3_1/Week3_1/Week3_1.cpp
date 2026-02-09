// Week3Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

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

Vector2 Minimum(const Vector2& a, const Vector2& b, const Vector2& c, int dim)
{
    // magnitude squared
    float aDimValue = (dim == 0) ? a.x : a.y;
    float bDimValue = (dim == 0) ? b.x : b.y;
    float cDimValue = (dim == 0) ? c.x : c.y;
    if (aDimValue < bDimValue && aDimValue < cDimValue)
    {
        return a;
    }
    else if (bDimValue < aDimValue && bDimValue < cDimValue)
    {
        return b;
    }

    return c;
}
// find min in the specific dimension
// dim can be 0 is x dimesion
// dim can be 1 is the y dimension
// k is the dimension
int gRecursiveCount = 0;
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
Vector2 FindMin(KDNode* node, int dim, int k)
{
    ++gRecursiveCount;
    if (node == nullptr)
    {
        Vector2 invalid;
        invalid.x = INT_MAX;
        invalid.y = INT_MAX;
        return invalid;
    }
    if (k == dim)
    {
        if (node->mLeft == nullptr)
        {
            return node->mData;
        }
        else
        {
            return FindMin(node->mLeft, dim, (k + 1) % 2);
        }
    }
    else
    {
        return Minimum(FindMin(node->mLeft, dim, (k + 1) % 2),
            FindMin(node->mRight, dim, (k + 1) % 2),
            node->mData,
            dim);
    }
}
void PrintRange(const Vector2& minRange, const Vector2& maxRange, KDNode* node, int k)
{
    ++gRecursiveCount;
    if (node != nullptr)
    {
        // if the value is within the min/max range
        if (minRange.x <= node->mData.x && minRange.y <= node->mData.y
            && node->mData.x <= maxRange.x && node->mData.y <= maxRange.y)
        {
            std::cout << "(" << node->mData.x << ", " << node->mData.y << ")\n";
        }
        // 0 looking at the x dimension
        if (k == 0)
        {
            // if minx is still smaller than current value, continue down the left branch
            if (minRange.x < node->mData.x)
            {
                PrintRange(minRange, maxRange, node->mLeft, (k + 1) % 2);
            }
            // if maxx is still larger than current value, continue down the right branch
            if (node->mData.x < maxRange.x)
            {
                PrintRange(minRange, maxRange, node->mRight, (k + 1) % 2);
            }
        }
        // 1 looking at the y dimension
        else
        {
            if (minRange.y < node->mData.y)
            {
                PrintRange(minRange, maxRange, node->mLeft, (k + 1) % 2);
            }
            if (node->mData.y < maxRange.y)
            {
                PrintRange(minRange, maxRange, node->mRight, (k + 1) % 2);
            }
        }
    }
}
KDNode* Delete(const Vector2& v, KDNode* node, int k)
{
    if (node == nullptr)
    {
        std::cout << "[ERROR] NODE WAS NOT FOUND";
        return node;
    }
    // we found the node
    if (v.x == node->mData.x && v.y == node->mData.y)
    {
        if (node->mRight != nullptr)
        {
            node->mData = FindMin(node->mRight, k, (k + 1) % 2);
            node->mRight = Delete(node->mData, node->mRight, (k + 1) % 2);
        }
        else if (node->mLeft != nullptr)
        {
            node->mData = FindMin(node->mLeft, k, (k + 1) % 2);
            node->mRight = Delete(node->mData, node->mLeft, (k + 1) % 2);
        }
        else
        {
            delete node;
            node = nullptr;
        }
    }
    else
    {
        // looking at the x dimension
        if (k == 0)
        {
            if (v.x < node->mData.x)
            {
                node->mLeft = Delete(v, node->mLeft, (k + 1) % 2);
            }
            else
            {
                node->mRight = Delete(v, node->mRight, (k + 1) % 2);
            }
        }
        // y dimension
        else
        {
            if (v.y < node->mData.y)
            {
                node->mLeft = Delete(v, node->mLeft, (k + 1) % 2);
            }
            else
            {
                node->mRight = Delete(v, node->mRight, (k + 1) % 2);
            }
        }
    }
    return node;
}
float DistSquared(const Vector2& v0, const Vector2& v1)
{
    Vector2 diff;
    diff.x = v0.x - v1.x;
    diff.y = v0.y - v1.y;
    return (diff.x * diff.x) + (diff.y * diff.y);
}
KDNode* Closest(KDNode* n0, KDNode* n1, const Vector2& v)
{
    if (n0 == nullptr)
        return n1;

    if (n1 == nullptr)
        return n0;

    long d1 = DistSquared(n0->mData, v);
    long d2 = DistSquared(n1->mData, v);

    if (d1 < d2)
        return n0;
    else
        return n1;
}
KDNode* NearestNeighbor(const Vector2& v, KDNode* node, int k)
{
    ++gRecursiveCount;
    if (node == nullptr)
    {
        return nullptr;
    }

    KDNode* nextBranch = nullptr;
    KDNode* otherBranch = nullptr;

    if (k == 0)
    {
        if (v.x < node->mData.x)
        {
            nextBranch = node->mLeft;
            otherBranch = node->mRight;
        }
        else
        {
            nextBranch = node->mRight;
            otherBranch = node->mLeft;
        }
    }
    else
    {
        if (v.y < node->mData.y)
        {
            nextBranch = node->mLeft;
            otherBranch = node->mRight;
        }
        else
        {
            nextBranch = node->mRight;
            otherBranch = node->mLeft;
        }
    }

    KDNode* temp = NearestNeighbor(v, nextBranch, (k + 1) % 2);
    KDNode* best = Closest(temp, node, v);

    float distSqr = DistSquared(v, best->mData);
    float planeDist = 0.0f;
    if (k == 0)
    {
        planeDist = v.x - node->mData.x;
    }
    else
    {
        planeDist = v.y - node->mData.y;
    }
    if (distSqr >= planeDist * planeDist)
    {
        temp = NearestNeighbor(v, otherBranch, (k + 1) % 2);
        best = Closest(temp, best, v);
    }

    return best;
}

void Exercise2KDTree()
{
    int maxValues = 200;
    Vector2 v;
    Vector2 deleteVector;
    int randomDeleteNodeIndex = rand() % maxValues;

    KDNode* root = nullptr;
    std::vector<Vector2> values;
    for (int i = 0; i < maxValues; ++i)
    {
        v.x = rand() % 501;
        v.y = rand() % 501;
        KDNode* newNode = Insert(v, root, 0);
        if (root == nullptr)
        {
            root = newNode;
        }
        std::cout << "(" << v.x << ", " << v.y << ")\n";
        values.push_back(v);
        if (i == randomDeleteNodeIndex)
        {
            deleteVector = v;
        }
    }

    std::cout << "\n\n";
    gRecursiveCount = 0;
    Vector2 minInX = FindMin(root, 0, 0);
    std::cout << "Find MinX Iterations: " << gRecursiveCount << "\n";
    gRecursiveCount = 0;
    Vector2 minInY = FindMin(root, 1, 0);
    std::cout << "Find MinY Iterations: " << gRecursiveCount << "\n";

    std::cout << "Min in the X: (" << minInX.x << ", " << minInX.y << ")\n";
    std::cout << "Min in the Y: (" << minInY.x << ", " << minInY.y << ")\n";

    std::cout << "\n\n";

    Vector2 minRange;
    Vector2 maxRange;
    minRange.x = (rand() % 101) + 100;
    minRange.y = (rand() % 101) + 100;
    maxRange.x = (rand() % 101) + 300;
    maxRange.y = (rand() % 101) + 300;
    std::cout << "Find in range: Min(" << minRange.x << ", " << minRange.y <<
        ") : Max(" << maxRange.x << ", " << maxRange.y << ")\n";
    gRecursiveCount = 0;
    PrintRange(minRange, maxRange, root, 0);
    std::cout << "Find Range Iterations: " << gRecursiveCount << "\n";

    std::cout << "\n\n";
    Vector2 target;
    target.x = rand() % 51 + 100;
    target.y = rand() % 51 + 100;
    gRecursiveCount = 0;
    KDNode* nearest = NearestNeighbor(target, root, 0);
    std::cout << "Target Node: (" << target.x << ", " << target.y << ")\n";
    std::cout << "Nearest Node: (" << nearest->mData.x << ", " << nearest->mData.y << ")\n";
    std::cout << "Nearest Iterations: " << gRecursiveCount << "\n";
    Vector2 n;
    float closestDist = FLT_MAX;
    for (auto& v : values)
    {
        float distSq = DistSquared(v, target);
        if (distSq < closestDist)
        {
            n = v;
            closestDist = distSq;
        }
    }
    std::cout << "Verify Target Node: (" << n.x << ", " << n.y << ")\n";

    std::cout << "\n\n";
    std::cout << "Delete Node: (" << deleteVector.x << ", " << deleteVector.y << ")\n";
    Delete(deleteVector, root, 0);
    minRange.x = 0;
    minRange.y = 0;
    maxRange.x = 500;
    maxRange.y = 500;
    PrintRange(minRange, maxRange, root, 0);

    DeleteKDTree(root);
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


int main()
{
    std::cout << "Hello World!\n";
    Exercise2KDTree();
}