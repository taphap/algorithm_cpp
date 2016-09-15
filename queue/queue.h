#pragma once

#define QUEUE_SIZE (10)

typedef int item_type;
typedef unsigned int size_type;

typedef struct tagQUEUE_S
{
    size_type front;
    size_type rear;
    size_type count;
    item_type queue[QUEUE_SIZE];
} QUEUE_S;

void initQueue(QUEUE_S* queue);
void enqueue(QUEUE_S* queue, item_type item);
item_type dequeue(QUEUE_S* queue);
bool isEmpty(QUEUE_S* queue);
size_type size(QUEUE_S* queue);