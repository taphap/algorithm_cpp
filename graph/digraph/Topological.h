#pragma once
#include "Digraph.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"

class Digraph;
class DirectedCycle;
class DepthFirstOrder;

class Topological
{
public:
    Topological(Digraph G);
    std::stack<int> order();
    bool isDAG();

private:
    std::stack<int> topoOrder;
};

Topological::Topological(Digraph G)
{
    DirectedCycle cycleFinder(G);
    
    if (!cycleFinder.hasCycle())
    {
        DepthFirstOrder orderFinder(G);
        topoOrder = orderFinder.reversePostOrder();
    }

    return;
}

std::stack<int> Topological::order()
{
    return topoOrder;
}

bool Topological::isDAG()
{
    return !topoOrder.empty();
}