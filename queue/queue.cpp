#include "queue.h"

void initQueue(QUEUE_S* queue)
{
    memset(queue, 0, sizeof(QUEUE_S));
    return;
}

/* 队列是否已满需在外层判断 */
void enqueue(QUEUE_S* queue, item_type item)
{
    queue->queue[queue->rear] = item;
    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->count++;
    return;
}

/* 队列是否为空需在外层判断 */
item_type dequeue(QUEUE_S* queue)
{
    item_type item;
    item = queue->queue[queue->front];
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->count--;
    return item;
}

bool isEmpty(QUEUE_S* queue)
{
    return queue->count == 0;
}

size_type size(QUEUE_S* queue)
{
    return queue->count;
}