#pragma once

#include"Vector.h"
#include <queue>
#include <limits>



template<typename T, typename W>
class WeightedGraph
{
public:
    struct Edge
    {
        int nodeIndex = -1;
        W weight;

        bool operator==(const Edge& rhs) const { return weight == rhs.weight; }
        bool operator<(const Edge& rhs) const { return weight < rhs.weight; }
        bool operator<=(const Edge& rhs) const { return weight <= rhs.weight; }
        bool operator>(const Edge& rhs) const { return weight > rhs.weight; }
        bool operator>=(const Edge& rhs) const { return weight >= rhs.weight; }
    };
    struct Node
    {
        const T* data = nullptr;
        // parent node for back tracking when finding the path
        Node* parent = nullptr;
        Vector<Edge> edges;
        // total weight for tracking when path finding
        W totalWeight;
    };


public:
    WeightedGraph()
    {

    }
    ~WeightedGraph()
    {
        Terminate();
    }

    void AddItem(const T* data)
    {
        Node* node = new Node();
        node->data = data;
        mNodes.PushBack(node);
    }
    void AddEdge(int a, int b, W weight)
    {
        if (a < 0 || a >= mNodes.Size() || b < 0 || b >= mNodes.Size())
        {
            return;
        }

        Edge edgeA = { b, weight };
        Edge edgeB = { a, weight };
        mNodes[a]->edges.PushBack(edgeA);
        mNodes[b]->edges.PushBack(edgeB);
    }

    W GetPath(int startNode, int endNode, Vector<const T*> pathOutput)
    {
        Reset();

        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> process;
        mNodes[startNode]->totalWeight = 0;
        process.push({ startNode, 0 });
        while (!process.empty())
        {
            Edge curEdge = process.top();
            process.pop();
            Node* node = mNodes[curEdge.nodeIndex];
            if (curEdge.weight > node->totalWeight)
            {
                continue;
            }
            if (curEdge.nodeIndex == endNode)
            {
                // we found the end, so break out
                break;
            }
            for (std::size_t i = 0; i < node->edges.Size(); ++i)
            {
                const Edge& edge = node->edges[i];
                Node* edgeNode = mNodes[edge.nodeIndex];

                if (node->totalWeight < std::numeric_limits<W>::max() && node->totalWeight + edge.weight < edgeNode->totalWeight)
                {
                    edgeNode->totalWeight = node->totalWeight + edge.weight;
                    edgeNode->parent = node;
                    process.push({ edge.nodeIndex, edgeNode->totalWeight });
                }
            }
        }

        pathOutput.Clear();
        Node* node = mNodes[endNode];
        W totalDistance = node->totalWeight;
        while (node != nullptr)
        {
            pathOutput.PushBack(node->data);
            node = node->parent;
        }

        return totalDistance;
    }

    void Terminate()
    {
        for (int i = 0; i < mNodes.Size(); ++i)
        {
            delete mNodes[i];
            mNodes[i] = nullptr;
        }
        mNodes.Clear();
    }
private:
    void Reset()
    {
        for (std::size_t i = 0; i < mNodes.Size(); ++i)
        {
            mNodes[i]->parent = nullptr;
            mNodes[i]->totalWeight = std::numeric_limits<W>::max();
        }
    }
    Vector<Node*> mNodes;
};