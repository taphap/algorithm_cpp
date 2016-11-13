#pragma once
#include "graph.h"

class Graph;

/* 检查图中是否有环 */
class Cycle
{
public:
    Cycle(Graph G);
    bool hasCycle();
private:
    bool cycle;
    std::vector<bool> marked;
    std::vector<int> edgeTo;
    void dfs(Graph G, int s);
};

Cycle::Cycle(Graph G)
{
    cycle = false;
    for (int v = 0; v < G.V(); v++)
    {
        marked.push_back(false);
        edgeTo.push_back(v);
    }

    for (int v = 0; v < G.V(); v++)
    {
        if (cycle)
        {
            return;
        }

        if (!marked[v])
        {
            dfs(G, v);
        }
    }
}

void Cycle::dfs(Graph G, int v)
{
    marked[v] = true;

    for (int w : G.adj(v))
    {
        if (!marked[w])
        {
            edgeTo[w] = v;
            dfs(G, w);
        }
        else
        {
            if (edgeTo[w] != v)
            {
                cycle = true;
                break;
            }
        }
    }

    return;
}

bool Cycle::hasCycle()
{
    return cycle;
}