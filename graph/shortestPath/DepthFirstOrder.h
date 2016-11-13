#pragma once
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include <stack>
#include <queue>

class DirectedEdge;
class EdgeWeightedDigraph;

class DepthFirstOrder
{
public:
    DepthFirstOrder(EdgeWeightedDigraph G);
    std::vector<int> preOrder();
    std::vector<int> postOrder();
    std::vector<int> reversePostOrder();

private:
    std::vector<bool> mark;
    std::queue<int> pre;
    std::queue<int> post;
    std::stack<int> reversePost;
    void dfs(EdgeWeightedDigraph G, int v);
};

DepthFirstOrder::DepthFirstOrder(EdgeWeightedDigraph G)
{
    for (int v = 0; v < G.V(); v++)
    {
        mark.push_back(false);
    }

    for (int v = 0; v < G.V(); v++)
    {
        if (!mark[v])
        {
            dfs(G, v);
        }
    }
}

void DepthFirstOrder::dfs(EdgeWeightedDigraph G, int v)
{
    pre.push(v);

    mark[v] = true;

    for (DirectedEdge e : G.adj(v))
    {
        if (!mark[e.to()])
        {
            dfs(G, e.to());
        }
    }

    post.push(v);
    reversePost.push(v);
}

std::vector<int> DepthFirstOrder::preOrder()
{
    std::vector<int> order;
    while (!pre.empty())
    {
        int v = post.front();
        post.pop();
        order.push_back(v);
    }

    return order;
}

std::vector<int> DepthFirstOrder::postOrder()
{
    std::vector<int> order;
    while (!post.empty())
    {
        int v = post.front();
        post.pop();
        order.push_back(v);
    }

    return order;
}

std::vector<int> DepthFirstOrder::reversePostOrder()
{
    std::vector<int> order;
    while (!reversePost.empty())
    {
        int v = reversePost.top();
        reversePost.pop();
        order.push_back(v);
    }

    return order;
}