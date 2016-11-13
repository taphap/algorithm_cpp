#pragma once
#include <iostream>
#include <fstream>
#include <vector>

/* 无向图类（邻接表表示） */
class Graph
{
public:
    Graph(int v);
    Graph(std::ifstream& in);
    int V();
    int E();
    void addEdge(int v, int w);
    std::vector<int> adj(int v);

private:
    int vertex;
    int edge;
    std::vector<std::vector<int>> adjacent;
};

Graph::Graph(int v)
{
    vertex = v;
    for (int i = 0; i < vertex; i++)
    {
        adjacent.push_back(std::vector<int>());
    }
}

Graph::Graph(std::ifstream& in)
{
    int  E, v, w;

    in >> vertex;
    in >> E;

    for (int i = 0; i < vertex; i++)
    {
        adjacent.push_back(std::vector<int>());
    }

    for (int i = 0; i < E; i++)
    {
        in >> v;
        in >> w;
        addEdge(v, w);
    }
}

int Graph::V(void)
{
    return vertex;
}

int Graph::E(void)
{
    return edge;
}

void Graph::addEdge(int v, int w)
{
    adjacent[v].push_back(w);
    adjacent[w].push_back(v);
    edge++;
}

std::vector<int> Graph::adj(int v)
{
    return adjacent[v];
}
