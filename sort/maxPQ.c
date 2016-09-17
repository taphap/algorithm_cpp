#include "maxPQ.h"

bool littlePQ(PRI_QUEUE_S* queue, size_type a, size_type b)
{
    return little(queue->pq[a], queue->pq[b]);
}

void exchPQ(PRI_QUEUE_S* queue, size_type a, size_type b)
{
    exch(&queue->pq[a], &queue->pq[b]);
}

/* 基于堆的优先队列 */
void initMaxPQ(PRI_QUEUE_S* queue)
{
    memset(queue, 0, sizeof(PRI_QUEUE_S));
    return;
}

bool isEmpty(PRI_QUEUE_S* queue)
{
    return queue->cnt == 0;
}

size_type size(PRI_QUEUE_S* queue)
{
    return queue->cnt;
}

/* k位置的元素上浮 */
void swim(PRI_QUEUE_S* queue, size_type k)
{
    while (k > 1)
    {
        if (littlePQ(queue, k / 2, k))
        {
            exchPQ(queue, k / 2, k);
            k = k / 2;
        }
    }
}

/* k位置的元素下沉 */
void sink(PRI_QUEUE_S* queue, size_type k)
{
    size_type j = 0;

    while (2 * k <= MAX_SIZE)
    {
        j = 2 * k;
        if (j < MAX_SIZE)
        {
            if (littlePQ(queue, k, k + 1))
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

void insert(PRI_QUEUE_S* queue, item_type v)
{
    queue->cnt++;
    queue->pq[queue->cnt] = v;
    swim(queue, queue->cnt);
    return;
}

item_type delMax(PRI_QUEUE_S* queue)
{
    item_type max = queue->pq[1];
    
    exch(&queue->pq[1], &queue->pq[queue->cnt]);
    queue->cnt--;
    sink(queue, 1);
    return max;
}
