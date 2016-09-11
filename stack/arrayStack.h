#ifndef STACK_H
#define STACK_H

/* ջ��С */
#define STACK_SIZE (10)

/* ջԪ������ */
typedef int item_type;

/* ջ��С���� */
typedef unsigned int size_type;

typedef int bool;

typedef struct tagSTACK_S
{
	size_type num;
	item_type  items[STACK_SIZE];
} STACK_S;

/* �ⲿ�ӿ� */
void initStack(STACK_S* stack);
bool isEmpty(STACK_S* stack);
size_type size(STACK_S* stack);
void push(STACK_S* stack, item_type item);
item_type pop(STACK_S* stack);

#endif