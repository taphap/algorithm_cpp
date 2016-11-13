#pragma once
#include <queue>
#include "Edge.h"
#include "EdgeWeightedGraph.h"

class Edge;
class EdgeWeightedGraph;

/* 延迟版Prim最小生成树算法(不将无效边从优先队列中删除，只是检查是否有效) */
class LazyPrimMST
{
public:
    LazyPrimMST(EdgeWeightedGraph G);
    void visit(EdgeWeightedGraph G, int v);
    std::vector<Edge> edges();
    double weight();

private:
    double mstWeight;
    std::vector<bool> marked;
    std::vector<Edge> mst;
    std::priority_queue<Edge, std::vector<Edge>> pq;
};

LazyPrimMST::LazyPrimMST(EdgeWeightedGraph G)
{
    for (int v = 0; v <= G.V(); v++)
    {
        marked.push_back(false);
    }

    visit(G, 0);
    while (!pq.empty())
    {
        Edge e = pq.top();
        pq.pop();

        int v = e.either();
        int w = e.other(v);
        if (marked[v] && marked[w])
        {
            continue;
        }

        mst.push_back(e);
        mstWeight += e.weight();
        if (!marked[v])
        {
            visit(G, v);
        }

        if (!marked[w])
        {
            visit(G, w);
        }
    }
}

void LazyPrimMST::visit(EdgeWeightedGraph G, int v)
{
    marked[v] = true;
    for (Edge e : G.adj(v))
    {
        if (!marked[e.other(v)])
        {
            pq.push(e);
        }
    }
}

std::vector<Edge> LazyPrimMST::edges()
{
    return mst;
}

double LazyPrimMST::weight()
{
    return mstWeight;
}