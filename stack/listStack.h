#include "list.h"

#ifndef LIST_STACK_H
#define LIST_STACK_H

typedef int item_type;
typedef unsigned int size_type;
typedef int bool;

typedef struct tagNODE_S
{
    item_type item;
    struct list_head listNode;
} NODE_S;

typedef struct tagSTACK_S
{
    size_type num;
    NODE_S item_head;
} STACK_S;

/* 外部接口 */
void initStack(STACK_S* stack);
bool isEmpty(STACK_S* stack);
size_type size(STACK_S* stack);
void push(STACK_S* stack, NODE_S* item);
item_type pop(STACK_S* stack);

#endif