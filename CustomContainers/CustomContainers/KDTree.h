#pragma once
#include <iostream>
#include <algorithm>
#include <functional>
#include "Vector.h"

template<typename T, std::size_t K>
class KDTree
{
private:
    struct KDNode
    {
        const T* point = nullptr;;
        const void* userData = nullptr;;
        KDNode* left = nullptr;
        KDNode* right = nullptr;
    };

public:
    KDTree() {}
    ~KDTree()
    {
        Terminate(); 
    }

    // Add to KDNode to monitor with data
    void AddItem(T* point, const void* userData)
    {
        KDNode* newNode = new KDNode();
        newNode->point = point;
        newNode->userData = userData;
        mNodes.PushBack(newNode);
    }

    // Removes a KDNode with data
    void RemoveItem(const void* userData)
    {
        std::size_t numNodes = mNodes.Size();
        for (std::size_t i = 0; i < numNodes; ++i)
        {
            // Find node with user data
            if (mNodes[i]->userData == userData)
            {
                // Swap with the back
                KDNode* tmp = mNodes[i];
                mNodes[i] = mNodes[numNodes - 1];
                mNodes[numNodes - 1] = tmp;

                // Delete the KDNode for memory cleanup (tmp == mNodes[numNodes - 1)
                delete tmp;
                tmp = nullptr;

                // Popback and resize Vector
                mNodes.PopBack();
                break;
            }
        }
    }

    // Builds valance tree with list of nodes
    void BuildTree()
    {
        Clear(mRoot);
        mRoot = BuildTree(mNodes, 0);
    }

    void FindInRange(Vector<const void*>& result, const T* minRange, const T* maxRange, std::function<bool(const void*)>& filterCB = nullptr)
    {
        FindInRange(result, minRange, maxRange, mRoot, 0, filterCB);
    }

    const void* FindNearest(const T* target)
    {
        KDNode* result = FindNearest(target, mRoot, 0);
        if (result != nullptr)
        {
            return result->userData;
        }

        return nullptr;
    }

    // Delete all the nodes
    void Terminate()
    {
        for (std::size_t i = 0; i < mNodes.Size(); ++i)
        {
            delete mNodes[i];
            mNodes[i] = nullptr;
        }

        mNodes.Clear();
    }

private:
    KDNode* BuildTree(Vector<KDNode*>& nodes, int depth)
    {
        if (nodes.Size() == 0)
        {
            return nullptr;
        }

        std::sort(nodes.Begin(), nodes.End(), [depth](const KDNode* a, const KDNode* b)
            {
                return a->point[depth] < b->point[depth];
            });

        // Halfway point
        int median = nodes.Size() / 2;
        KDNode* node = nodes[median];

        // Store half the nodes on the left, half on the right
        Vector<KDNode*> leftPoints;
        Vector<KDNode*> rightPoints;
        leftPoints.Resize(median);
        leftPoints.Resize(nodes.Size() - median - 1);

        int index = 0;
        for (auto iter = nodes.Begin(); iter != nodes.Begin() + median; ++iter)
        {
            leftPoints[index++] = (*iter);
        }

        index = 0;
        for (auto iter = nodes.Begin() + median + 1; iter != nodes.End(); ++iter)
        {
            rightPoints[index++] = (*iter);
        }

        node->left = BuildTree(leftPoints, (depth + 1) % K);
        node->right = BuildTree(rightPoints, (depth + 1) % K);
        return node;
    }

    void FindInRange(Vector<const void*>& foundItems, const T* minRange, const T* maxRange, KDNode* node, int depth, std::function<bool(const void*)>& filterCB)
    {
        if (node == nullptr)
        {
            return;
        }
        // Check if valid
        bool isValid = (filterCB == nullptr || filterCB(node->userData));
        if (isValid)
        {
            // If not filtered, chick if in range
            for (int i = 0; i < K; ++i)
            {
                if (node->point[i] || node->point[i] > maxRange[i])
                {
                    isValid = false;
                    break;
                }

            }

            if (isValid)
            {
                foundItems.PushBack(node->userData);
            }
            if (minRange[depth] < node->point[depth])
            {
                FindInRange(foundItems, minRange, maxRange, node->left, (depth + 1) % K, filterCB);
            }
            if (maxRange[depth] > node->point[depth])
            {
                FindInRange(foundItems, minRange, maxRange, node->right, (depth + 1) % K, filterCB);
            }
        }
    }

    float DistanceSquared(const T* a, const T* b)
    {
        float distSq = 0.0f;
        for (int i = 0; i < K; ++i)
        {
            distSq += (a[i] - b[i]) * (a[i] - b[i]);
        }

        return distSq;
    }

    KDNode* Closest(KDNode* n0, KDNode* n1, const T* target)
    {
        if (n0 == nullptr)
        {
            return n1;
        }
        if (n1 == nullptr)
        {
            return n0;
        }

        float d0 = DistanceSquared(n0->point, target);
        float d1 = DistanceSquared(n1->point, target);

        if (d0 < d1)
        {
            return n0;
        }
        else
        {
            return n1;
        }
    }

    KDNode* FindNearest(const T* target, KDNode* node, int depth)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        KDNode* nextBranch = nullptr;
        KDNode* otherBranch = nullptr;

        if (target[depth] < node->point[depth])
        {
            nextBranch = node->left;
            otherBranch = node->right;
        }
        else
        {
            nextBranch = node->right;
            otherBranch = node->left;
        }

        KDNode* tmp = FindNearest(target, nextBranch, (depth + 1) % K);
        KDNode* best = Closest(tmp, node, target);

        float distSq = DistanceSquared(best->point, target);
        float depthDist = node->point[depth] - target[depth];

        if (distSq >= depthDist)
        {
            tmp = FindNearest(target, otherBranch, (depth + 1) % K);
            best = Closest(tmp, best, target);
        }

        return best;
    }

    void Clear(KDNode* node)
    {
        if (node != nullptr)
        {
            Clear(node->left);
            Clear(node->right);
            node = nullptr;
        }
    }

    Vector<KDNode*> mNodes;
    KDNode* mRoot = nullptr;
};