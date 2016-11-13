#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "graph.h"

class Graph;

int degree(Graph G, int v)
{
	int degree = 0;
	for (int w : G.adj(v))
	{
		degree++;
	}
	return degree;
}

int maxDegree(Graph G)
{
	int max = 0;
	int tmpDegree = 0;

	for (int v = 0; v < G.V(); v++)
	{
		tmpDegree = degree(G, v);
		if (tmpDegree > max)
		{
			max = tmpDegree;
		}
	}
	
	return max;
}

double avgDegree(Graph G)
{
	return 2.0 * G.E() / G.V();
}

int numberOfSelfLoops(Graph G)
{
	int count = 0;
	for (int v = 0; v < G.V(); v++)
	{
		for (int w : G.adj(v))
		{
			if (v == w)
			{
				count++;
			}
		}
	}

	return count / 2;
}

void toString(Graph G)
{
	std::ostringstream s;
	std::stringstream tmp;
	s << G.V();
	s << " vertices\n";
	s << G.E();
	s << " edges\n";

	for (int v = 0; v < G.V(); v++)
	{
		s << v;
		s << ": ";
		for (int w : G.adj(v))
		{
			s << w;
			s << " ";
		}
		s << "\n";
	}

	std::cout << s.str();
	return;
}