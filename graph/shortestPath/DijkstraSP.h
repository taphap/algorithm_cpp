#pragma once
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "IndexMinPQ.h"

class DirectedEdge;
class EdgeWeightedDigraph;

class DijkstraSP
{
public:
    DijkstraSP(EdgeWeightedDigraph G, int s);
    double distTo(int v);
    bool hasPathTo(int v);
    std::vector<DirectedEdge> pathTo(int v);

private:
    std::vector<DirectedEdge> edgeTo;
    std::vector<double> disTo;
    IndexMinPQ<double> *pq = nullptr;
    void relax(EdgeWeightedDigraph G, int v);
};

DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
    pq = new IndexMinPQ<double>(G.V());

    for (int v = 0; v < G.V(); v++)
    {
        edgeTo.push_back(DirectedEdge(v, v, 0.0));
        disTo.push_back(INFINITY);
    }

    disTo[s] = 0.0;
    pq->insert(s, 0.0);

    while (!pq->isEmpty())
    {
        relax(G, pq->delMin());
    }
}

void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
    for (DirectedEdge e : G.adj(v))
    {
        int w = e.to();
        if (disTo[w] > disTo[v] + e.weight())
        {
            disTo[w] = disTo[v] + e.weight();
            edgeTo[w] = e;
            if (!pq->contains(w))
            {
                pq->insert(w, disTo[w]);
            }
            else
            {
                pq->change(w, disTo[w]);
            }
        }
    }
}

double DijkstraSP::distTo(int v)
{
    return disTo[v];
}

bool DijkstraSP::hasPathTo(int v)
{
    return disTo[v] < INFINITY;
}

std::vector<DirectedEdge> DijkstraSP::pathTo(int v)
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