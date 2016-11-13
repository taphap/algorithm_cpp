#pragma once
#include "graph.h"

class Graph;

class DepthFirstPaths
{
public:
    DepthFirstPaths(Graph G, int s);
    bool hasPathTo(int v);
    std::vector<int> pathTo(int v);

private:
    std::vector<int> edgeTo;
    std::vector<bool> mark;
    int start;
    void dfs(Graph G, int w);
};

DepthFirstPaths::DepthFirstPaths(Graph G, int s)
{
    /* 初始化节点状态标记和路径记录结构 */
    for (int i = 0; i < G.V(); i++)
    {
        mark.push_back(false);
        edgeTo.push_back(i);
    }

    start = s;

    dfs(G, s);
}

void DepthFirstPaths::dfs(Graph G, int v)
{
    mark[v] = true;
    
    for (int w : G.adj(v))
    {
        if (!mark[w])
        {
            edgeTo[w] = v;
            dfs(G, w);
        }
    }
}

/* 是否存在s到v的路径 */
bool DepthFirstPaths::hasPathTo(int v)
{
    return mark[v];
}

/* 从s到v的路径 */
std::vector<int> DepthFirstPaths::pathTo(int v)
{
    std::vector<int> path;

    if (!hasPathTo(v))
    {
        return path;
    }

    for (int w = v; w != start; w = edgeTo[w])
    {
        path.push_back(w);
    }

    path.push_back(start);
    return path;
}