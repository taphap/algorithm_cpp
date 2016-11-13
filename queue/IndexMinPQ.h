#pragma once
#include <vector>
#include <algorithm>

template<typename T>
class IndexMinPQ
{
public:
	IndexMinPQ(int maxN);
	bool isEmpty();
	bool contains(int k);
	void insert(int k, T key);
	void change(int k, T key);
	T min();
	int delMin();
	int size();

private:
	int N = 0;
	std::vector<int> pq;
	std::vector<int> qp;
	std::vector<T> keys;
	bool greater(int i, int j);
	void exch(int i, int j);
	void swim(int k);
	void sink(int k);
};

template<typename T>
IndexMinPQ<T>::IndexMinPQ(int maxN)
{
	T tmp = INFINITY;
	keys.push_back(tmp);
	for (int i = 0; i < maxN + 1; i++)
	{
		keys.push_back(tmp);
		pq.push_back(0);
		qp.push_back(-1);
	}
}

template<typename T>
bool IndexMinPQ<T>::isEmpty()
{
	return N == 0;
}

template<typename T>
bool IndexMinPQ<T>::contains(int k)
{
	return qp[k] != -1;
}

template<typename T>
void IndexMinPQ<T>::insert(int k, T key)
{
	N++;
	qp[k] = N;
	pq[N] = k;
	keys[k] = key;
	swim(N);
}

template<typename T>
T IndexMinPQ<T>::min()
{
	return keys[pq[1]];
}

template<typename T>
int IndexMinPQ<T>::delMin()
{
	T tmp = INFINITY;
	int indexOfMin = pq[1];
	exch(1, N--);
	sink(1);
	keys[pq[N + 1]] = tmp;
	qp[pq[N + 1]] = -1;
	return indexOfMin;
}

template<typename T>
int IndexMinPQ<T>::size()
{
	return N;
}

template<typename T>
bool IndexMinPQ<T>::greater(int i, int j)
{
	return  keys[pq[i]] > keys[pq[j]];
}

template<typename T>
void IndexMinPQ<T>::exch(int i, int j)
{
	int swap = pq[i];
	pq[i] = pq[j];
	pq[j] = swap;
	qp[pq[i]] = i;
	qp[pq[j]] = j;
}

template<typename T>
void IndexMinPQ<T>::swim(int k)
{
	while (k > 1 && greater(k / 2, k))
	{
		exch(k / 2, k);
		k = k / 2;
	}
}

template<typename T>
void IndexMinPQ<T>::sink(int k)
{
	while (2 * k <= N)
	{
		int j = 2 * k;
		if (j < N && greater(j, j + 1))
		{
			j++;
		}

		if (!greater(k, j))
		{
			break;
		}

		exch(k, j);
		k = j;
	}
}

template<typename T>
void IndexMinPQ<T>::change(int k, T key)
{
	keys[k] = key;
	swim(qp[k]);
	sink(qp[k]);
}