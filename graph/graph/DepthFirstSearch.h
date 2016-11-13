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
    /* �����нڵ�״̬��ʼ��Ϊδ��� */
    for (int v = 0; v < G.V(); v++)
    {
        mark.push_back(false);
    }

    dfs(G, s);
}

/* ���ڵ�w�Ƿ�ͬs��ͨ */
bool DepthFirstSearch::marked(int w)
{
    return mark[w];
}

/* ��s��ͨ�Ķ����� */
int DepthFirstSearch::count()
{
    return cnt;
}

/* ����������� */
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