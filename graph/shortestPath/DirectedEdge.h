#pragma once

class DirectedEdge
{
public:
	DirectedEdge(int v, int w, double wt);
	double weight();
	int from();
	int to();

private:
	int v1;
	int w2;
	double Weight;
};

DirectedEdge::DirectedEdge(int v, int w, double wt)
{
	v1 = v;
	w2 = w;
	Weight = wt;
}

double DirectedEdge::weight()
{
	return Weight;
}

int DirectedEdge::from()
{
	return v1;
}

int DirectedEdge::to()
{
	return w2;
}
