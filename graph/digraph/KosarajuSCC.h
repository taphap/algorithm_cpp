#pragma once
#include "Digraph.h"
#include "DepthFirstOrder.h"

class Digraph;
class DepthFirstOrder;

/* ��ͼ�е�ǿ��ͨ������
��DFSһ�鷴��ͼ��Ȼ�����սڵ���������ԭͼ����DFS,
��ͬһ��DFS���нڵ㼴��ǿ��ͨ�ģ���DFSԭͼ��DFS����ͼҲ���ԣ� */
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

/* ͼ��ǿ��ͨ�������� */
int KosarajuSCC::count()
{
    return cnt;
}

/* �ж������ڵ��Ƿ�ǿ��ͨ */
bool KosarajuSCC::stronglyConnected(int v, int w)
{
    return connectedId[v] == connectedId[w];
}

/* ��ȡ�ڵ�������ǿ��ͨ����ID */
int KosarajuSCC::id(int v)
{
    return connectedId[v];
}