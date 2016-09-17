#include "insertionSort.h"

/* ≤Â»Î≈≈–Ú */
void insertionSort(item_type a[MAX_SIZE])
{
    size_t i, j;

    for (i = 1; i < MAX_SIZE; i++)
    {
        for (j = i; j > 0 && (little(a[j], a[j - 1])); j--)
        {
            exch(&a[j], &a[j - 1]);
        }
    }
}