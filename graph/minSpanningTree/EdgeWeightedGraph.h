#pragma once
#include <vector>
#include <fstream>
#include "Edge.h"

class Edge;

class EdgeWeightedGraph
{
public:
	EdgeWeightedGraph(int V);
	EdgeWeightedGraph(std::ifstream& in);
	int V();
	int E();
	void addEdge(Edge e);
	std::vector<Edge> adj(int v);
	std::vector<Edge> edges();

private:
	int Vertexs;
	int Edges;
	std::vector<std::vector<Edge>> adjacent;
};

EdgeWeightedGraph::EdgeWeightedGraph(int v)
{
	Vertexs = v;
	Edges = 0;
	for (int i = 0; i < Vertexs; i++)
	{
		adjacent.push_back(std::vector<Edge>());
	}
}

EdgeWeightedGraph::EdgeWeightedGraph(std::ifstream& in)
{
	int v, w, eds;
	double wt;

	in >> Vertexs;
	in >> eds;

	for (int i = 0; i < Vertexs; i++)
	{
		adjacent.push_back(std::vector<Edge>());
	}

	for (int i = 0; i < eds; i++)
	{
		in >> v;
		in >> w;
		in >> wt;
		Edge e(v, w, wt);
		addEdge(e);
	}
}

int EdgeWeightedGraph::V()
{
	return Vertexs;
}

int EdgeWeightedGraph::E()
{
	return Edges;
}

void EdgeWeightedGraph::addEdge(Edge e)
{
	int v = e.either();
	int w = e.other(v);

	adjacent[v].push_back(e);
	adjacent[w].push_back(e);
	Edges++;
}

std::vector<Edge> EdgeWeightedGraph::adj(int v)
{
	return adjacent[v];
}

std::vector<Edge> EdgeWeightedGraph::edges()
{
	std::vector<Edge> b;
	for (int v = 0; v < Vertexs; v++)
	{
		for (Edge e : adjacent[v])
		{
			if (e.other(v) > v)
			{
				b.push_back(e);
			}
		}
	}

	return b;
}
