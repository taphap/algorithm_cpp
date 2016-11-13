#pragma once
#include <vector>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "Topological.h"

class DirectedEdge;
class EdgeWeightedDigraph;
class Topological;

class AcyclicSP
{
public:
    AcyclicSP(EdgeWeightedDigraph G, int s);
    double distTo(int v);
    bool hasPathTo(int v);
    std::vector<DirectedEdge> pathTo(int v);

private:
    std::vector<DirectedEdge> edgeTo;
    std::vector<double> distanceTo;
    void relax(EdgeWeightedDigraph G, int v);
};

AcyclicSP::AcyclicSP(EdgeWeightedDigraph G, int s)
{
    for (int v = 0; v < G.V(); v++)
    {
        edgeTo.push_back(DirectedEdge(v, v, 0.0));
        distanceTo.push_back(INFINITY);
    }

    distanceTo[s] = 0.0;

    Topological topo(G);
    
    for (int v : topo.order())
    {
        relax(G, v);
    }
}

void AcyclicSP::relax(EdgeWeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {
        int w = e.to();
        if (distanceTo[w] > distanceTo[v] + e.weight())
        {
            distanceTo[w] = distanceTo[v] + e.weight();
            edgeTo[w] = e;
        }
    }
}

double AcyclicSP::distTo(int v)
{
    return distanceTo[v];
}

bool AcyclicSP::hasPathTo(int v)
{
    return distanceTo[v] < INFINITY;
}

std::vector<DirectedEdge> AcyclicSP::pathTo(int v)
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
