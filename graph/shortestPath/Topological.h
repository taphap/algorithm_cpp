#pragma once
#include <vector>
#include "EdgeWeightedDigraph.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"

class Digraph;
class DirectedCycle;
class DepthFirstOrder;

class Topological
{
public:
    Topological(EdgeWeightedDigraph G);
    std::vector<int> order();
    bool isDAG();

private:
    std::vector<int> topoOrder;
};

Topological::Topological(EdgeWeightedDigraph G)
{
    DirectedCycle cycleFinder(G);
    
    if (!cycleFinder.hasCycle())
    {
        DepthFirstOrder orderFinder(G);
        topoOrder = orderFinder.reversePostOrder();
    }

    return;
}

std::vector<int> Topological::order()
{
    return topoOrder;
}

bool Topological::isDAG()
{
    return !topoOrder.empty();
}