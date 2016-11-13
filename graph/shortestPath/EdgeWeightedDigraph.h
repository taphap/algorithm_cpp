#pragma once
#include <vector>
#include <fstream>
#include <deque>
#include "DirectedEdge.h"

class DirectedEdge;

class EdgeWeightedDigraph
{
public:
	EdgeWeightedDigraph(int v);
	EdgeWeightedDigraph(std::ifstream& in);
	int V();
	int E();
	void addEdge(DirectedEdge e);
	std::vector<DirectedEdge> adj(int v);
	std::deque<DirectedEdge> edges();

private:
	int vertexs;
	int edge;
	std::vector<std::vector<DirectedEdge>> adjacent;
};

EdgeWeightedDigraph::EdgeWeightedDigraph(int v)
{
	vertexs = v;
	edge = 0;
	for (int i = 0; i < vertexs; i++)
	{
		adjacent.push_back(std::vector<DirectedEdge>());
	}
}

EdgeWeightedDigraph::EdgeWeightedDigraph(std::ifstream& in)
{
	int v, w, eds;
	double wt;

	in >> vertexs;
	in >> eds;

	for (int i = 0; i < vertexs; i++)
	{
		adjacent.push_back(std::vector<DirectedEdge>());
	}

	for (int i = 0; i < eds; i++)
	{
		in >> v;
		in >> w;
		in >> wt;
		DirectedEdge e(v, w, wt);
		addEdge(e);
	}
}

int EdgeWeightedDigraph::V()
{
	return vertexs;
}

int EdgeWeightedDigraph::E()
{
	return edge;
}

void EdgeWeightedDigraph::addEdge(DirectedEdge e)
{
	adjacent[e.from()].push_back(e);
	edge++;
}

std::vector<DirectedEdge> EdgeWeightedDigraph::adj(int v)
{
	return adjacent[v];
}

std::deque<DirectedEdge> EdgeWeightedDigraph::edges()
{
	std::deque<DirectedEdge> tmp;
	for (int v = 0; v < vertexs; v++)
	{
		for (DirectedEdge e : adj(v))
		{
			tmp.push_front(e);
		}
	}

	return tmp;
}