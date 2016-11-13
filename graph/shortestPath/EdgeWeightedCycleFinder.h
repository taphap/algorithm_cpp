#pragma once
#include <vector>
#include <deque>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"

class DirectedEdge;
class EdgeWeightedDigraph;

class EdgeWeightedCycleFinder
{
public:
    EdgeWeightedCycleFinder(EdgeWeightedDigraph G);
    bool hasCycle(void);
    std::vector<DirectedEdge> cycle(void);

private:
    std::vector<bool> marked;
    std::vector<DirectedEdge> edgeTo;
    std::vector<DirectedEdge> cyc;
    std::vector<bool> onStack;
    void dfs(EdgeWeightedDigraph G, int v);
};

EdgeWeightedCycleFinder::EdgeWeightedCycleFinder(EdgeWeightedDigraph G)
{
    for (int i = 0; i < G.V(); i++)
    {
        marked.push_back(false);
        edgeTo.push_back(DirectedEdge(i, i, 0.0));
        onStack.push_back(false);
    }

    for (int i = 0; i < G.V(); i++)
    {
        if (!marked[i])
        {
            dfs(G, i);
        }
    }
}

bool EdgeWeightedCycleFinder::hasCycle()
{
    return !cyc.empty();
}

std::vector<DirectedEdge> EdgeWeightedCycleFinder::cycle()
{
    return cyc;
}

void EdgeWeightedCycleFinder::dfs(EdgeWeightedDigraph G, int v)
{
    int w;
    marked[v] = true;
    onStack[v] = true;

    for (DirectedEdge e : G.adj(v))
    {
        w = e.to();
        if (hasCycle())
        {
            return;
        }
        else if (!marked[w])
        {
            edgeTo[w] = e;
            dfs(G, w);
        }
        else if (onStack[w])
        {
            while (e.from() != w)
            {
                cyc.push_back(e);
                e = edgeTo[e.from()];
            }

            cyc.push_back(e);
        }
    }
    onStack[v] = false;
}