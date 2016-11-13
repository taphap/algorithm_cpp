// graph.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "graph.h"
#include "toolFunc.h"
#include "DepthFirstSearch.h"
#include "DepthFirstPaths.h"
#include "BreadthFirstPaths.h"
#include "CC.h"
#include "Cycle.h"
#include "TwoColor.h"

using std::ifstream;
using std::string;
using std::ostringstream;

int main()
{
    ifstream input("tinyG.txt");
    Graph G(input);

    DepthFirstSearch dfs(G, 0);
    DepthFirstPaths dfsPath(G, 0);

    BreadthFirstPaths bfsPath(G, 0);
    CC cc(G);
    Cycle cyc(G);
    TwoColor color(G);

    for (int i : dfsPath.pathTo(4))
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (int i : bfsPath.pathTo(4))
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    std::cout << cc.count() << " components\n";
    for (int i = 0; i < cc.count(); i++)
    {
        for (int j = 0; j < G.V(); j++)
        {
            if (i == cc.id(j))
            {
                std::cout << j << " ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "Has cycle " << cyc.hasCycle() << "\n";
    std::cout << "Able two color " << color.isTwoColor() << "\n";
    toString(G);
    return 0;
}


