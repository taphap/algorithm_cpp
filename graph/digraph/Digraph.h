#pragma once
#include <vector>
#include <fstream>

class Digraph
{
public:
	Digraph(int v);
	Digraph(std::ifstream& in);
	int V();
	int E();
	void addEdge(int v, int w);
	std::vector<int> adj(int v);
	Digraph reverse();

private:
	int vertexs;
	int edges;
	std::vector<std::vector<int>> adjacent;
};

Digraph::Digraph(int v)
{
	vertexs = v;
	edges = 0;
	for (int i = 0; i < v; i++)
	{
		adjacent.push_back(std::vector<int>());
	}
}

Digraph::Digraph(std::ifstream& in)
{
	int E, v, w;

	in >> vertexs;
	in >> E;
	for (int i = 0; i < vertexs; i++)
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

int Digraph::V()
{
	return vertexs;
}

int Digraph::E()
{
	return edges;
}

std::vector<int> Digraph::adj(int v)
{
	return adjacent[v];
}

void Digraph::addEdge(int v, int w)
{
	adjacent[v].push_back(w);
	edges++;
}

Digraph Digraph::reverse()
{
	Digraph R(vertexs);

	for (int v = 0; v < vertexs; v++)
	{
		for (int w : adj(v))
		{
			R.addEdge(w, v);
		}
	}
	return R;
}