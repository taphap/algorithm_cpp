#pragma once
#include <vector>

class WeightedQuickUnion
{
public:
    WeightedQuickUnion(int N);
    int count();
    bool connected(int p, int q);
    void combine(int p, int q);
    int find(int p);

private:
    std::vector<int> id;
    std::vector<int> sz;
    int cnt;
};

WeightedQuickUnion::WeightedQuickUnion(int N)
{
    cnt = N;

    for (int n = 0; n < N; n++)
    {
        id.push_back(n);
        sz.push_back(1);
    }
}

int WeightedQuickUnion::count()
{
    return cnt;
}

bool WeightedQuickUnion::connected(int p, int q)
{
    return find(p) == find(q);
}

int WeightedQuickUnion::find(int p)
{
    while (id[p] != p)
    {
        p = id[p];
    }

    return p;
}

void WeightedQuickUnion::combine(int p, int q)
{
    int i = find(p);
    int j = find(q);

    if (i == j)
    {
        return;
    }

    /* 将小树链接到大树的根节点 */
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }

    cnt--;
}