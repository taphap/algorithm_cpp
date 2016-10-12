#pragma once
#include "rbtree.h"

typedef int key_type;
typedef int value_type;
typedef unsigned int size_type;

typedef struct tagTEST_NODE_S
{
    key_type key;
    value_type value;
    struct rb_node rbNode;
} TEST_NODE_S;

TEST_NODE_S* get(struct rb_root* root, key_type k);
void put(struct rb_root* root, key_type k, value_type v);
TEST_NODE_S* min(struct rb_root* root);
//TEST_NODE_S* floor(struct rb_root* root, key_type k);
//TEST_NODE_S* select(struct rb_root* root, size_type k);
//size_type rankNode(struct rb_root* root, key_type k);
//void deleteMin(struct rb_root* root);
void deleteNode(struct rb_root* root, key_type k);
void printForEach(struct rb_root* node);
void destoryTree(struct rb_root* root);