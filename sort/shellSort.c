#include "shellSort.h"

/* Shell排序--间隔不为1的插入排序 */
void shellSort(item_type a[MAX_SIZE])
{
    size_t i, j;
    size_t h = 1;

    /* 选取最大的排序间隔 */
    while (h < MAX_SIZE / 3)
    {
        h = 3 * h + 1;
    }

    while (h >= 1)
    {
        /* 内部是间隔为h的插入排序 */
        for (i = h; i < MAX_SIZE; i++)
        {
            for (j = i; j >= h && (little(a[j], a[j - h])); j -= h)
            {
                exch(&a[j], &a[j - h]);
            }
        }

        h = h / 3;
    }
}
