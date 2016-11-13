// digraph.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Digraph.h"
#include "DirectedDFS.h"
#include "DirectedCycle.h"
#include "KosarajuSCC.h"

using std::ifstream;
using std::string;
using std::ostringstream;

int main()
{
    ifstream input("tinyDG.txt");
    Digraph DG(input);

    DirectedCycle DC(DG);
    KosarajuSCC SCC(DG);

    if (DC.hasCycle())
    {
        for (int i : DC.cycle())
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "The Directed Graph has no cycle.\n";
    }

    std::cout << "The Directed Graph has " << SCC.count() << " strongly connected compoents.\n";
    return 0;
}

