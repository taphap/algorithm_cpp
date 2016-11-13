#pragma once
#include <queue>
#include "Edge.h"
#include "EdgeWeightedGraph.h"
#include "WeightedQuickUnion.h"

class Edge;
class EdgeWeightedGraph;
class WeightedQuickUnion;

class KruskalMST
{
public:
    KruskalMST(EdgeWeightedGraph G);
    std::vector<Edge> edges();
    double weight();

private:
    std::vector<Edge> mst;
    double mstWeight;
};

KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
    std::priority_queue<Edge, std::vector<Edge>> mstPriQueue;
    WeightedQuickUnion uf(G.V());

    for (Edge e : G.edges())
    {
        mstPriQueue.push(e);
    }

    while (!mstPriQueue.empty() && mst.size() < (size_t)(G.V() - 1))
    {
        Edge e = mstPriQueue.top();
        mstPriQueue.pop();
        
        int v = e.either();
        int w = e.other(v);

        if (uf.connected(v, w))
        {
            continue;
        }

        uf.combine(v, w);
        mst.push_back(e);
        mstWeight += e.weight();
    }
}

double KruskalMST::weight()
{
    return mstWeight;
}

std::vector<Edge> KruskalMST::edges()
{
    return mst;
}