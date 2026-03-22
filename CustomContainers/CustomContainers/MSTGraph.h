#pragma once


#include "Vector.h"
#include <queue>

template<typename T, typename W = int>
class MSTGraph
{
public:
    struct Edge
    {
        int fromIndex = -1;
        int toIndex = -1;
        W weight;

        bool operator<(const Edge& rhs) const { return weight < rhs.weight; }
        bool operator<=(const Edge& rhs) const { return weight <= rhs.weight; }
        bool operator==(const Edge& rhs) const { return weight == rhs.weight; }
        bool operator>(const Edge& rhs) const { return weight > rhs.weight; }
        bool operator>=(const Edge& rhs) const { return weight >= rhs.weight; }
    };
    struct Node
    {
        const T* data = nullptr;
        bool isVisited = false;
        bool addedToProcess = false;
        W bestWeight;
        Vector<Edge> edges;
    };
public:
    MSTGraph()
    {

    }
    ~MSTGraph()
    {
        Terminate();
    }

    void AddItem(const T* data)
    {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->isVisited = false;
        newNode->addedToProcess = false;
        newNode->bestWeight = W();
        mNodes.PushBack(newNode);
    }

    void AddEdge(int a, int b, W weight, bool bothWays = true)
    {
        if (a < 0 || a >= mNodes.Size() || b < 0 || b >= mNodes.Size())
        {
            return;
        }
        Edge edgeA = { a, b, weight };
        mNodes[a]->edges.PushBack(edgeA);
        if (bothWays)
        {
            Edge edgeB = { b, a, weight };
            mNodes[b]->edges.PushBack(edgeB);
        }
    }
    void GenerateMST(int startNode)
    {
        // going to use Prims Algorithm
        Reset();
        mMSTGraph.Clear();

        // use the std version so that we can use a difference compare function
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> process;
        process.push({ -1, startNode, 0 });
        while (!process.empty())
        {
            Edge edge = process.top();
            process.pop();
            Node* node = mNodes[edge.toIndex];
            if (!node->isVisited)
            {
                node->isVisited = true;
                if (edge.fromIndex != -1)
                {
                    mMSTGraph.PushBack(edge);
                }
                for (std::size_t i = 0; i < node->edges.Size(); ++i)
                {
                    const Edge& edge = node->edges[i];
                    Node* toNode = mNodes[edge.toIndex];
                    if (!toNode->isVisited && (!toNode->addedToProcess || edge.weight < toNode->bestWeight))
                    {
                        toNode->addedToProcess = true;
                        toNode->bestWeight = edge.weight;
                        process.push(edge);
                    }
                }
            }
        }
    }
    const Vector<Edge>& GetMST() const
    {
        return mMSTGraph;
    }
    void Terminate()
    {
        for (size_t i = 0; i < mNodes.Size(); ++i)
        {
            delete mNodes[i];
            mNodes[i] = nullptr;
        }
        mNodes.Clear();
    }
private:
    void Reset()
    {
        for (size_t i = 0; i < mNodes.Size(); ++i)
        {
            mNodes[i]->isVisited = false;
            mNodes[i]->addedToProcess = false;
            mNodes[i]->bestWeight = W();
        }
    }
    Vector<Node*> mNodes;
    Vector<Edge> mMSTGraph;
};