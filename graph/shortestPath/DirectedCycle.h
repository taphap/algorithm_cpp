#pragma once
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include <stack>

class DirectedEdge;
class EdgeWeightedDigraph;

class DirectedCycle
{
public:
    DirectedCycle(EdgeWeightedDigraph G);
    bool hasCycle();
    std::vector<int> cycle();

private:
    bool cycleFlag;
    std::vector<bool> mark;
    std::vector<bool> onStack;
    std::vector<int> edgeTo;
    std::stack<int> cyclePath;
    void dfs(EdgeWeightedDigraph G, int v);
};

DirectedCycle::DirectedCycle(EdgeWeightedDigraph G)
{
    cycleFlag = false;

    for (int v = 0; v < G.V(); v++)
    {
        mark.push_back(false);
        onStack.push_back(false);
        edgeTo.push_back(v);
    }

    for (int v = 0; v < G.V(); v++)
    {
        if (!mark[v])
        {
            dfs(G, v);
        }
    }
}

void DirectedCycle::dfs(EdgeWeightedDigraph G, int v)
{
    onStack[v] = true;
    mark[v] = true;

    for (DirectedEdge e : G.adj(v))
    {
        if (cycleFlag)
        {
            return;
        }

        int w = e.to();

        if (!mark[w])
        {
            edgeTo[w] = v;
            dfs(G, w);
        }
        else
        {
            if (onStack[w])
            {
                cycleFlag = true;
                for (int x = v; x != w; x = edgeTo[x])
                {
                    cyclePath.push(x);
                }

                cyclePath.push(w);
                cyclePath.push(v);
            }
        }
    }

    onStack[v] = false;
}

bool DirectedCycle::hasCycle()
{
    return cycleFlag;
}

std::vector<int> DirectedCycle::cycle()
{
    std::vector<int> cyc;

    while (!cyclePath.empty())
    {
        int v = cyclePath.top();
        cyclePath.pop();
        cyc.push_back(v);
    }

    return cyc;
}