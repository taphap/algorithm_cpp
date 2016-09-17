#include "quickSort.h"

void shuffleArray(item_type a[MAX_SIZE])
{
    return;
}

size_t partition(item_type a[MAX_SIZE], size_t lo, size_t hi)
{
    size_t i = lo;
    size_t j = hi + 1;
    item_type v = a[lo];

    while (true)
    {
        while (little(a[++i], v))
        {
            if (i == hi)
            {
                break;
            }
        }

        while (little(v, a[--j]))
        {
            if (j == lo)
            {
                break;
            }
        }

        if (i >= j)
        {
            break;
        }
        exch(&a[i], &a[j]);
    }

    exch(&a[lo], &a[j]);

    return j;
}

void _quickSort(item_type a[MAX_SIZE], size_t lo, size_t hi)
{
    size_t j = 0;

    if (hi <= lo)
    {
        return;
    }

    /* 按首元素切分 */
    j = partition(a, lo, hi);
    if (j == lo)
    {
        _quickSort(a, j + 1, hi);
    }
    else if (j == hi)
    {
        _quickSort(a, lo, j - 1);
    }
    else
    {
        _quickSort(a, lo, j - 1);
        _quickSort(a, j + 1, hi);
    }
}

void quickSort(item_type a[MAX_SIZE])
{
    /* 打散数组 */
    shuffleArray(a);
    _quickSort(a, 0, MAX_SIZE - 1);
}
