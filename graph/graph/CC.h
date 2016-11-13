#pragma once
#include "graph.h"

class Graph;

/* 获取图中有多少连通分量(connect component) */
class CC
{
public:
    CC(Graph G);
    bool connected(int v, int w);
    int count();
    int id(int v);

private:
    int cnt;
    std::vector<int> componentId;
    std::vector<bool> marked;
    void dfs(Graph G, int s);
};

CC::CC(Graph G)
{
    cnt = 0;

    for (int v = 0; v < G.V(); v++)
    {
        componentId.push_back(v);
        marked.push_back(false);
    }

    for (int v = 0; v < G.V(); v++)
    {
        if (!marked[v])
        {
            cnt++;
            dfs(G, v);
        }
    }
}

void CC::dfs(Graph G, int v)
{
    marked[v] = true;
    componentId[v] = cnt;

    for (int w : G.adj(v))
    {
        if (!marked[w])
        {
            dfs(G, w);
        }
    }

    return;
}

/* 检查节点v和w是否连通 */
bool CC::connected(int v, int w)
{
    return componentId[v] == componentId[w];
}

/* 图中连通分量个数 */
int CC::count()
{
    return cnt;
}

/* 节点v所属的连通分量id */
int CC::id(int v)
{
    return componentId[v];
}