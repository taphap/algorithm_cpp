#pragma once
#include "graph.h"

#define BLACK (0)
#define RED (1)
#define NO_COLOR (2)

class Graph;

/* 是否是二分图(可以用两种颜色进行着色) */
class TwoColor
{
public:
    TwoColor(Graph G);
    bool isTwoColor();

private:
    bool twoColorFlag;
    std::vector<bool> marked;
    std::vector<int> colors;
    void dfs(Graph G, int s, int color);
};

TwoColor::TwoColor(Graph G)
{
    twoColorFlag = true;
    for (int v = 0; v < G.V(); v++)
    {
        marked.push_back(false);
        colors.push_back(NO_COLOR);
    }

    for (int v = 0; v < G.V(); v++)
    {
        if (!twoColorFlag)
        {
            return;
        }

        if (!marked[v])
        {
            dfs(G, v, BLACK);
        }
    }
}

void TwoColor::dfs(Graph G, int v, int color)
{
    marked[v] = true;
    colors[v] = color;
    int versaColor;

    if (BLACK == color)
    {
        versaColor = RED;
    }
    else
    {
        versaColor = BLACK;
    }

    for (int w : G.adj(v))
    {
        if (!marked[w])
        {
            dfs(G, w, versaColor);
        }
        else
        {
            if (colors[w] != versaColor)
            {
                twoColorFlag = false;
                return;
            }
        }
    }
}

bool TwoColor::isTwoColor()
{
    return twoColorFlag;
}