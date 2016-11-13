#pragma once
#include "graph.h"

class Graph;

class DepthFirstSearch
{
public:
    DepthFirstSearch(Graph G, int s);
    bool marked(int w);
    int count();

private:
    void dfs(Graph G, int v);
    std::vector<bool> mark;
    int cnt;
};

DepthFirstSearch::DepthFirstSearch(Graph G, int s)
{
    /* 将所有节点状态初始化为未标记 */
    for (int v = 0; v < G.V(); v++)
    {
        mark.push_back(false);
    }

    dfs(G, s);
}

/* 检查节点w是否同s连通 */
bool DepthFirstSearch::marked(int w)
{
    return mark[w];
}

/* 与s连通的顶点数 */
int DepthFirstSearch::count()
{
    return cnt;
}

/* 深度优先搜索 */
void DepthFirstSearch::dfs(Graph G, int v)
{
    mark[v] = true;
    cnt++;

    for (int w : G.adj(v))
    {
        if (!mark[w])
        {
            dfs(G, w);
        }
    }

    return;
}