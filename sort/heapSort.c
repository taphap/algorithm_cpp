#include "maxPQ.h"
#include "heapSort.h"
#include "utility.h"

/* kλ�õ�Ԫ���³�,�Ѵ�СΪN */
void sinkSort(PRI_QUEUE_S* queue, size_type k, size_type N)
{
    size_type j = 0;

    while (2 * k <= N)
    {
        j = 2 * k;
        if (j < N)
        {
            if (littlePQ(queue, j, j + 1))
            {
                j++;
            }
        }

        if (!littlePQ(queue, k, j))
        {
            break;
        }

        exchPQ(queue, k, j);
        k = j;
    }
}

void heapSort(PRI_QUEUE_S* queue)
{
    size_type k = 0;
    size_type N = MAX_SIZE;

    /* ����� */
    for (k = N / 2; k >= 1; k--)
    {
        sinkSort(queue, k, N);
    }

    /* �³����� */
    while (N > 1)
    {
        exchPQ(queue, 1, N);
        N--;
        sinkSort(queue, 1, N);
    }

    return;
}