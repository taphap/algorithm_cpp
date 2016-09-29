#pragma once
#include <stdio.h>

#define offset(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define	 list_entry(ptr, type, member)  ((type *)(void *)((char *)(ptr) - offset(type, member)))

typedef unsigned int size_type;

typedef struct tagBST_NODE_S
{
    struct tagBST_NODE_S* left;
    struct tagBST_NODE_S* right;
    size_type cnt;
} BST_NODE_S;

typedef struct tagBST_ROOT_S
{
    BST_NODE_S* node;
} BST_ROOT_S;

size_type size(BST_NODE_S* node);
