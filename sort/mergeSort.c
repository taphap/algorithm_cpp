#include "mergeSort.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

void merge(item_type a[MAX_SIZE], size_t lo, size_t mid, size_t hi)
{
    item_type aux[MAX_SIZE];
    size_t k;
    size_t i = lo;
    size_t j = mid + 1;

    for (k = lo; k <= hi; k++)
    {
        aux[k] = a[k];
    }

    for (k = lo; k <= hi; k++)
    {
        if (i > mid)
        {
            a[k] = aux[j++];
        }
        else if (j > hi)
        {
            a[k] = aux[i++];
        }
        else if (little(aux[j], aux[i]))
        {
            a[k] = aux[j++];
        }
        else
        {
            a[k] = aux[i++];
        }
    }
}

void _mergeSort(item_type a[MAX_SIZE], size_t lo, size_t hi)
{
    if (hi <= lo)
    {
        return;
    }

    size_t mid = lo + (hi - lo) / 2;
    _mergeSort(a, lo, mid);
    _mergeSort(a, mid + 1, hi);
    merge(a, lo, mid, hi);
}

/* 归并排序，递归方式，自顶向下 */
void mergeSort(item_type a[MAX_SIZE])
{
    _mergeSort(a, 0, MAX_SIZE - 1);
}

/* 归并排序，非递归，自底向上 */
void mergeSortBU(item_type a[MAX_SIZE])
{
    size_t sz;
    size_t lo;

    for (sz = 1; sz < MAX_SIZE; sz += sz)
    {
        for (lo = 0; lo < MAX_SIZE - sz; lo += sz + sz)
        {
            merge(a, lo, lo + sz - 1, min(lo + sz + sz - 1, MAX_SIZE - 1));
        }
    }
}
