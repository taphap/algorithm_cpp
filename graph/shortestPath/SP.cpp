// SP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "IndexMinPQ.h"
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "DijkstraSP.h"
#include "AcyclicSP.h"
#include "BellmanFordSP.h"
using std::ifstream;
using std::cout;

void printPath(std::vector<DirectedEdge> path)
{
    int v, w;
    std::vector<DirectedEdge>::reverse_iterator rIter;

    for (rIter = path.rbegin(); rIter != path.rend(); rIter++)
    {
        v = rIter->from();
        w = rIter->to();
        cout << v << " -> " << w << " ";
    }

    cout << "\n";
}

int main()
{
    ifstream positiveEdgeHasCycle("tinyEWD.txt");
    ifstream noCycle("tinyEWDAG.txt");
    ifstream negativeEdgeNoNegativeCycle("tinyEWDn.txt");
    ifstream negativeCycle("tinyEWDnc.txt");
    EdgeWeightedDigraph EWD(positiveEdgeHasCycle);
    EdgeWeightedDigraph EWDAG(noCycle);
    EdgeWeightedDigraph EWDN(negativeEdgeNoNegativeCycle);
    EdgeWeightedDigraph EWDNC(negativeCycle);
    DijkstraSP DJKSP(EWD, 0);
    AcyclicSP ACSP(EWDAG, 5);
    BellmanFordSP BFSP(EWDN, 0);
    BellmanFordSP BFSPNC(EWDNC, 0);

    cout << "Dijkstra Shortest Path:\n";
    for (int v = 0; v < EWD.V(); v++)
    {
        if (DJKSP.hasPathTo(v))
        {
            printPath(DJKSP.pathTo(v));
        }
        else
        {
            cout << "Has no path from 0 to " << v << "\n";
        }
    }
    
    cout << "Acyclic Shortest Path:\n";
    for (int v = 0; v < EWDAG.V(); v++)
    {
        if (ACSP.hasPathTo(v))
        {
            printPath(ACSP.pathTo(v));
        }
        else
        {
            cout << "Has no path from 5 to " << v << "\n";
        }
    }

    cout << "BellmanFord Shortest Path:\n";
    if (BFSP.hasNegativeCycle())
    {
        cout << "The Digraph has negative cycle, not exist shortest path.\n";
        printPath(BFSP.negativeCycle());
    }
    else
    {
        for (int v = 0; v < EWD.V(); v++)
        {
            if (BFSP.hasPathTo(v))
            {
                printPath(BFSP.pathTo(v));
            }
            else
            {
                cout << "Has no path from 0 to " << v << "\n";
            }
        }
    }

    cout << "BellmanFord Shortest Path:\n";
    if (BFSPNC.hasNegativeCycle())
    {
        cout << "The Digraph has negative cycle, not exist shortest path.\n";
        printPath(BFSPNC.negativeCycle());
    }
    else
    {
        for (int v = 0; v < EWD.V(); v++)
        {
            if (BFSP.hasPathTo(v))
            {
                printPath(BFSP.pathTo(v));
            }
            else
            {
                cout << "Has no path from 0 to " << v << "\n";
            }
        }
    }

    return 0;
}

