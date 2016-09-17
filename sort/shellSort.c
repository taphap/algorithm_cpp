#include "shellSort.h"

/* Shell����--�����Ϊ1�Ĳ������� */
void shellSort(item_type a[MAX_SIZE])
{
    size_t i, j;
    size_t h = 1;

    /* ѡȡ���������� */
    while (h < MAX_SIZE / 3)
    {
        h = 3 * h + 1;
    }

    while (h >= 1)
    {
        /* �ڲ��Ǽ��Ϊh�Ĳ������� */
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
