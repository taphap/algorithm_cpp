#pragma once
#include "graph.h"
#include <queue>

class Graph;

/* ��������������ҳ���·�������·�� */
class BreadthFirstPaths
{
public:
    BreadthFirstPaths(Graph G, int s);
    bool hasPathTo(int v);
    std::vector<int> pathTo(int v);

private:
    std::vector<int> edgeTo;
    std::vector<bool> mark;
    int start;
    void bfs(Graph G, int v);
};

BreadthFirstPaths::BreadthFirstPaths(Graph G, int s)
{
    for (int i = 0; i < G.V(); i++)
    {
        mark.push_back(false);
        edgeTo.push_back(i);
    }

    bfs(G, s);
}

void BreadthFirstPaths::bfs(Graph G, int v)
{
    std::queue<int> bfsQueue;
    int front;
    mark[v] = true;
    bfsQueue.push(v);

    while (!bfsQueue.empty())
    {
        front = bfsQueue.front();
        bfsQueue.pop();
        for (int w : G.adj(front))
        {
            if (!mark[w])
            {
                edgeTo[w] = front;
                mark[w] = true;
                bfsQueue.push(w);
            }
        }
    }
}

/* �Ƿ����s��v��·�� */
bool BreadthFirstPaths::hasPathTo(int v)
{
    return mark[v];
}

/* ��s��v��·�� */
std::vector<int> BreadthFirstPaths::pathTo(int v)
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