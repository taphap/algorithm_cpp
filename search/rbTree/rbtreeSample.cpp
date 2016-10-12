#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "rbtreeSample.h"

int compareTo(key_type m, key_type n)
{
    if (m > n)
    {
        return 1;
    }
    else if (m < n)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void freeNode(struct rb_node* node)
{
    TEST_NODE_S* tmpNode = NULL;

    tmpNode = rb_entry(node, TEST_NODE_S, rbNode);
    if (NULL != tmpNode)
    {
        free(tmpNode);
    }

    return;
}

TEST_NODE_S* _get(struct rb_node* node, key_type k)
{
    TEST_NODE_S* tmpNode = NULL;
    int cmp = 0;

    if (NULL == node)
    {
        return NULL;
    }

    tmpNode = rb_entry(node, TEST_NODE_S, rbNode);
    cmp = compareTo(k, tmpNode->key);
    if (0 == cmp)
    {
        return tmpNode;
    }
    else if (cmp < 0)
    {
        return _get(node->rb_left, k);
    }
    else
    {
        return _get(node->rb_right, k);
    }
}

TEST_NODE_S* get(struct rb_root* root, key_type k)
{
    return _get(root->rb_node, k);
}

void put(struct rb_root* root, key_type k, value_type v)
{
    int cmp = 0;
    struct rb_node **tmpRbNode = &(root->rb_node);
    struct rb_node *parent = NULL;
    TEST_NODE_S* newNode = NULL;
    TEST_NODE_S* tmpNode = NULL;

    newNode = (TEST_NODE_S*)malloc(sizeof(TEST_NODE_S));
    if (NULL == newNode)
    {
        return;
    }
    memset(newNode, 0, sizeof(TEST_NODE_S));
    newNode->key = k;
    newNode->value = v;

    /* Figure out where to put new node */
    while (*tmpRbNode) 
    {
        tmpNode = rb_entry(*tmpRbNode, TEST_NODE_S, rbNode);
        cmp = compareTo(k, tmpNode->key);

        parent = *tmpRbNode;
        if (cmp < 0)
        {
            tmpRbNode = &((*tmpRbNode)->rb_left);
        }
        else if (cmp > 0)
        {
            tmpRbNode = &((*tmpRbNode)->rb_right);
        }
        else
        {
            return;
        }
    }

    /* Add new node and rebalance tree. */
    rb_link_node(&newNode->rbNode, parent, tmpRbNode);
    rb_insert_color(&newNode->rbNode, root);

    return;
}

TEST_NODE_S* min(struct rb_root* root)
{
    struct rb_node* node = NULL;

    node = rb_first(root);
    return rb_entry(node, TEST_NODE_S, rbNode);
}

void deleteNode(struct rb_root* root, key_type k)
{
    TEST_NODE_S* tmpNode = get(root, k);
    if (NULL != tmpNode) {
        rb_erase(&(tmpNode->rbNode), root);
        freeNode(&(tmpNode->rbNode));
    }
}

void destoryTree(struct rb_root* root)
{
    struct rb_node* parent = NULL;
    struct rb_node* node = NULL;

    if (NULL == root)
    {
        return;
    }

    node = root->rb_node;
    while (node)
    {
        if (NULL != node->rb_left)
        {
            node = node->rb_left;
            continue;
        }

        if (NULL != node->rb_right)
        {
            node = node->rb_right;
            continue;
        }

        if (node == root->rb_node)
        {
            freeNode(node);
            root->rb_node = NULL;
            break;
        }

        parent = rb_parent(node);
        if (node == parent->rb_left)
        {
            freeNode(node);
            parent->rb_left = NULL;
            if (NULL != parent->rb_right)
            {
                node = parent->rb_right;
            }
            else
            {
                node = parent;
            }
            continue;
        }

        freeNode(node);
        parent->rb_right = NULL;
    }
}

void printForEach(struct rb_root* root)
{
    struct rb_node* node = NULL;
    TEST_NODE_S* tmpNode = NULL;

    for (node = rb_first(root); node; node = rb_next(node))
    {
        tmpNode = rb_entry(node, TEST_NODE_S, rbNode);
        if (NULL != tmpNode)
        {
            std::cout << tmpNode->value << std::endl;
        }
    }
}