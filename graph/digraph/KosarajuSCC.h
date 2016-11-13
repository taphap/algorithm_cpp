#pragma once
#include "Digraph.h"
#include "DepthFirstOrder.h"

class Digraph;
class DepthFirstOrder;

/* 求图中的强连通分量，
先DFS一遍反向图，然后依照节点的逆后续对原图进行DFS,
在同一个DFS树中节点即是强连通的（先DFS原图后DFS反向图也可以） */
class KosarajuSCC
{
public:
    KosarajuSCC(Digraph G);
    bool stronglyConnected(int v, int w);
    int count();
    int id(int v);

private:
    std::vector<bool> mark;
    std::vector<int> connectedId;
    int cnt;
    void dfs(Digraph G, int v);
};

KosarajuSCC::KosarajuSCC(Digraph G)
{
    for (int v = 0; v < G.V(); v++)
    {
        mark.push_back(false);
        connectedId.push_back(v);
    }

    cnt = 0;
    DepthFirstOrder revertDfs(G.reverse());

    for (int v : revertDfs.reversePostOrder())
    {
        if (!mark[v])
        {
            cnt++;
            dfs(G, v);
        }
    }
}

void KosarajuSCC::dfs(Digraph G, int v)
{
    mark[v] = true;
    connectedId[v] = cnt;

    for (int w : G.adj(v))
    {
        if (!mark[w])
        {
            dfs(G, w);
        }
    }
}

/* 图中强连通分量个数 */
int KosarajuSCC::count()
{
    return cnt;
}

/* 判断两个节点是否强连通 */
bool KosarajuSCC::stronglyConnected(int v, int w)
{
    return connectedId[v] == connectedId[w];
}

/* 获取节点所属的强连通分量ID */
int KosarajuSCC::id(int v)
{
    return connectedId[v];
}