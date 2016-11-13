#pragma once
#include "Digraph.h"

class Digraph;

class DirectedDFS
{
public:
    DirectedDFS(Digraph G, int s);
    bool isReachable(int v);

private:
    std::vector<bool> mark;
    void dfs(Digraph G, int v);
};

DirectedDFS::DirectedDFS(Digraph G, int s)
{
    for (int v = 0; v < G.V(); v++)
    {
        mark.push_back(false);
    }

    dfs(G, s);
}

void DirectedDFS::dfs(Digraph G, int v)
{
    mark[v] = true;

    for (int w : G.adj(v))
    {
        if (!mark[w])
        {
            dfs(G, w);
        }
    }
}

bool DirectedDFS::isReachable(int v)
{
    return mark[v];
}