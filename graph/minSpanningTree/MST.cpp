// MST.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "Edge.h"
#include "EdgeWeightedGraph.h"
#include "LazyPrimMST.h"
#include "KruskalMST.h"

using std::ifstream;
using std::cout;

int main()
{
    ifstream input("tinyEWG_NEGATIVE.txt");
    EdgeWeightedGraph EWG(input);
    LazyPrimMST LPMST(EWG);
    KruskalMST KMST(EWG);

    cout << EWG.V() << " ";
    cout << EWG.E() << "\n";

    for (Edge e : EWG.edges())
    {
        cout << e.either() << " ";
        cout << e.other(e.either()) << " ";
        cout << e.weight() << "\n";
    }

    cout << "Lazy Prim MST:\n";

    for (Edge e : LPMST.edges())
    {
        cout << e.either() << " ";
        cout << e.other(e.either()) << " ";
        cout << e.weight() << "\n";
    }

    cout << "Kruskal MST:\n";

    for (Edge e : KMST.edges())
    {
        cout << e.either() << " ";
        cout << e.other(e.either()) << " ";
        cout << e.weight() << "\n";
    }
    return 0;
}


