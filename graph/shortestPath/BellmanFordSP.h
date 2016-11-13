#pragma once
#include <vector>
#include <queue>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedCycleFinder.h"

class DiretedEdge;
class EdgeWeightedDigraph;
class EdgeWeightedCycleFinder;

class BellmanFordSP
{
public:
    BellmanFordSP(EdgeWeightedDigraph G, int s);
    double distTo(int v);
    bool hasPathTo(int v);
    std::vector<DirectedEdge> pathTo(int v);
    bool hasNegativeCycle();
    std::vector<DirectedEdge> negativeCycle();

private:
    int cost;
    std::queue<int> tmpQueue;
    std::vector<bool> onQueue;
    std::vector<DirectedEdge> edgeTo;
    std::vector<double> distanceTo;
    std::vector<DirectedEdge> cycle;
    void relax(EdgeWeightedDigraph G, int v);
    void findNegativeCycle();
};

BellmanFordSP::BellmanFordSP(EdgeWeightedDigraph G, int s)
{
    for (int v = 0; v < G.V(); v++)
    {
        edgeTo.push_back(DirectedEdge(v, v, 0.0));
        onQueue.push_back(false);
        distanceTo.push_back(INFINITY);
    }

    distanceTo[s] = 0.0;
    tmpQueue.push(s);
    onQueue[s] = true;

    while (!tmpQueue.empty() && !hasNegativeCycle())
    {
        int w = tmpQueue.front();
        tmpQueue.pop();
        onQueue[w] = false;
        relax(G, w);
    }
}

void BellmanFordSP::relax(EdgeWeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {
        int w = e.to();
        if (distanceTo[w] > distanceTo[v] + e.weight())
        {
            distanceTo[w] = distanceTo[v] + e.weight();
            edgeTo[w] = e;
            if (!onQueue[w])
            {
                tmpQueue.push(w);
                onQueue[w] = true;
            }
        }
    }

    cost++;

    if (0 == cost % G.V())
    {
        findNegativeCycle();
    }
}

double BellmanFordSP::distTo(int v)
{
    return distanceTo[v];
}

bool BellmanFordSP::hasPathTo(int v)
{
    return distanceTo[v] < INFINITY;
}

std::vector<DirectedEdge> BellmanFordSP::pathTo(int v)
{
    std::vector<DirectedEdge> path;
    DirectedEdge e = edgeTo[v];

    if (!hasPathTo(v))
    {
        return path;
    }

    for (; e.from() != e.to(); e = edgeTo[e.from()])
    {
        path.push_back(e);
    }

    path.push_back(e);

    return path;
}

void BellmanFordSP::findNegativeCycle()
{
    int V = edgeTo.size();
    EdgeWeightedDigraph spt(V);
    
    for (int v = 0; v < V; v++)
    {
        if (edgeTo[v].from() != edgeTo[v].to())
        {
            spt.addEdge(edgeTo[v]);
        }
    }

    EdgeWeightedCycleFinder cf(spt);

    cycle = cf.cycle();
}

bool BellmanFordSP::hasNegativeCycle()
{
    return !cycle.empty();
}

std::vector<DirectedEdge> BellmanFordSP::negativeCycle()
{
    return cycle;
}