#pragma once

#include "Vector.h"
#include "Globals.h"

class DisjointSetUnion
{
public:
    DisjointSetUnion(int numNodes)
    {
        mParent.Resize(numNodes);
        mRank.Resize(numNodes);
        for (int i = 0; i < numNodes; ++i)
        {
            mParent[i] = i;
            mRank[i] = 0;
        }
    }
    int FindParentIndex(int nodeIndex)
    {
        if (mParent[nodeIndex] != nodeIndex)
        {
            mParent[nodeIndex] = FindParentIndex(mParent[nodeIndex]);
        }
        return mParent[nodeIndex];
    }
    bool UniteEdges(int from, int to)
    {
        int rootFrom = FindParentIndex(from);
        int rootTo = FindParentIndex(to);
        if (rootFrom == rootTo)
        {
            return false;
        }
        if (mRank[rootFrom] < mRank[rootTo])
        {
            mParent[rootFrom] = rootTo;
        }
        else if (mRank[rootFrom] > mRank[rootTo])
        {
            mParent[rootTo] = rootFrom;
        }
        else
        {
            mParent[rootTo] = rootFrom;
            ++mRank[rootFrom];
        }
        return true;
    }
private:
    Vector<int> mParent;
    Vector<int> mRank;
};

template<typename W>
class MSTGraphK
{
public:
    struct Edge
    {
        int fromNode = -1;
        int toNode = -1;
        W weight;
    };
public:
    void Clear()
    {
        mEdges.Clear();
        mMSTGraph.Clear();
        mNumNodes = 0;
    }
    void SetNodeCount(int numNodes)
    {
        mNumNodes = numNodes;
    }
    void AddEdge(int a, int b, W weight)
    {
        Edge newEdge = { a, b, weight };
        mEdges.PushBack(newEdge);
    }
    void GenerateMST()
    {
        mMSTGraph.Clear();

        DisjointSetUnion dsu(mNumNodes);
        Globals::IntroSort(mEdges.Begin(), mEdges.End(), [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
        for (std::size_t i = 0; i < mEdges.Size(); ++i)
        {
            const Edge& edge = mEdges[i];
            if (dsu.UniteEdges(edge.fromNode, edge.toNode))
            {
                mMSTGraph.PushBack(edge);
                if (mMSTGraph.Size() == mNumNodes - 1)
                {
                    break;
                }
            }
        }
    }
    const Vector<Edge>& GetMST() const
    {
        return mMSTGraph;
    }
private:
    int mNumNodes = 0;
    Vector<Edge> mEdges;
    Vector<Edge> mMSTGraph;
};