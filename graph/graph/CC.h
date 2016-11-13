#pragma once
#include "graph.h"

class Graph;

/* ��ȡͼ���ж�����ͨ����(connect component) */
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

/* ���ڵ�v��w�Ƿ���ͨ */
bool CC::connected(int v, int w)
{
    return componentId[v] == componentId[w];
}

/* ͼ����ͨ�������� */
int CC::count()
{
    return cnt;
}

/* �ڵ�v��������ͨ����id */
int CC::id(int v)
{
    return componentId[v];
}