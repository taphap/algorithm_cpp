#pragma once
#include <iostream>
#include "binaryST.h"

typedef int key_type;
typedef int value_type;

typedef struct tagTEST_NODE_S
{
    key_type key;
    value_type value;
    BST_NODE_S bNode;
} TEST_NODE_S;

TEST_NODE_S* get(BST_ROOT_S* root, key_type k);
void put(BST_ROOT_S* root, key_type k, value_type v);
TEST_NODE_S* min(BST_ROOT_S* root);
TEST_NODE_S* floor(BST_ROOT_S* root, key_type k);
TEST_NODE_S* select(BST_ROOT_S* root, size_type k);
size_type rankNode(BST_ROOT_S* root, key_type k);
void deleteMin(BST_ROOT_S* root);
void deleteNode(BST_ROOT_S* root, key_type k);
void printForEach(BST_NODE_S* node);
