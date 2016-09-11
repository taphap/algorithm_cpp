#include "listStack.h"
#include <string.h>

void initStack(STACK_S* stack)
{
    stack->num = 0;
    LIST_HEAD(list_stack);
    INIT_LIST_HEAD(&(stack->item_head.listNode));
    memset(stack->item_head.item, 0, sizeof(item_type));
}

bool isEmpty(STACK_S* stack)
{
    return stack->num == 0;
}

size_type size(STACK_S* stack)
{
    return stack->num;
}

void push(STACK_S* stack, NODE_S* item)
{
    list_add(&(item->listNode), &(stack->item_head.listNode));
    stack->num++;
    return;
}

item_type pop(STACK_S* stack)
{
    NODE_S* node = list_entry(&(stack->item_head.listNode), NODE_S, listNode);
    item_type item = node->item;

    list_del(&(stack->item_head.listNode));
    free(node);
    stack->num--;
    return item;
}