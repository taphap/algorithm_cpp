#ifndef STACK_H
#define STACK_H

/* 栈大小 */
#define STACK_SIZE (10)

/* 栈元素类型 */
typedef int item_type;

/* 栈大小类型 */
typedef unsigned int size_type;

typedef int bool;

typedef struct tagSTACK_S
{
	size_type num;
	item_type  items[STACK_SIZE];
} STACK_S;

/* 外部接口 */
void initStack(STACK_S* stack);
bool isEmpty(STACK_S* stack);
size_type size(STACK_S* stack);
void push(STACK_S* stack, item_type item);
item_type pop(STACK_S* stack);

#endif