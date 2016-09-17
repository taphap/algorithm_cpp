#pragma once
#include "utility.h"

typedef unsigned int size_type;

typedef struct tagPRI_QUEUE_S
{
    size_type cnt;
    item_type pq[MAX_SIZE + 1];
} PRI_QUEUE_S;

void initMaxPQ(PRI_QUEUE_S* queue);
bool isEmpty(PRI_QUEUE_S* queue);
size_type size(PRI_QUEUE_S* queue);
void insert(PRI_QUEUE_S* queue, item_type v);
item_type delMax(PRI_QUEUE_S* queue);
/********************************************************/
void sink(PRI_QUEUE_S* queue, size_type k);
void exchPQ(PRI_QUEUE_S* queue, size_type a, size_type b);
bool littlePQ(PRI_QUEUE_S* queue, size_type a, size_type b);
void exchPQ(PRI_QUEUE_S* queue, size_type a, size_type b);