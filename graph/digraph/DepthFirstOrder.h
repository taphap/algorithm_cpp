#pragma once
#include "Digraph.h"
#include <stack>
#include <queue>

class Digraph;

class DepthFirstOrder
{
public:
    DepthFirstOrder(Digraph G);
    std::vector<int> preOrder();
    std::vector<int> postOrder();
    std::vector<int> reversePostOrder();

private:
    std::vector<bool> mark;
    std::queue<int> pre;
    std::queue<int> post;
    std::stack<int> reversePost;
    void dfs(Digraph G, int v);
};

DepthFirstOrder::DepthFirstOrder(Digraph G)
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

void DepthFirstOrder::dfs(Digraph G, int v)
{
    pre.push(v);

    mark[v] = true;

    for (int w : G.adj(v))
    {
        if (!mark[w])
        {
            dfs(G, w);
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