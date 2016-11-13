#pragma once
#include <string>
#include <stdexcept>

class Edge
{
public:
	Edge(int v, int w, double wt);
	Edge();
	double weight();
	int either();
	int other(int vertex);
	int compareTo(Edge that);
    bool operator < (const Edge& that) const
    {
        return that.Weight < Weight;
    }

private:
	int v1;
	int w2;
	double Weight;
};

Edge::Edge()
{
	v1 = 0;
	w2 = 0;
	Weight = 0;
}

Edge::Edge(int v, int w, double wt)
{
	v1 = v;
	w2 = w;
	Weight = wt;
}

double Edge::weight()
{
	return Weight;
}

int Edge::either()
{
	return v1;
}

int Edge::other(int vertex)
{
	if (vertex == v1)
	{
		return w2;
	}
	else if (vertex == w2)
	{
		return v1;
	}
	else
	{
		throw std::runtime_error("Inconsistent edge");
	}
}

int Edge::compareTo(Edge that)
{
	if (weight() < that.weight())
	{
		return -1;
	}
	else if (weight() > that.weight())
	{
		return +1;
	}
	else
	{
		return 0;
	}
}
