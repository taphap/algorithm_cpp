#include "arrayStack.h"
#include <string.h>

void initStack(STACK_S* stack)
{
	memset(stack, 0, sizeof(STACK_S));
}

bool isEmpty(STACK_S* stack)
{
	return stack->num == 0;
}

size_type size(STACK_S* stack)
{
	return stack->num;
}

void push(STACK_S* stack, item_type item)
{
	stack->items[stack->num] = item;
	stack->num++;
	return;
}

item_type pop(STACK_S* stack)
{
	stack->num--;
	return stack->items[stack->num];
}
