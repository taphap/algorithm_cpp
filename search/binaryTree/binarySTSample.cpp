#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "binarySTSample.h"

using std::cout;
using std::endl;

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

TEST_NODE_S* _get(BST_NODE_S* node, key_type k)
{
    TEST_NODE_S* tmpNode = NULL;
    int cmp = 0;

    if (NULL == node)
    {
        return NULL;
    }

    tmpNode = list_entry(node, TEST_NODE_S, bNode);
    cmp = compareTo(k, tmpNode->key);
    if (0 == cmp)
    {
        return tmpNode;
    }
    else if (cmp < 0)
    {
        return _get(node->left, k);
    }
    else
    {
        return _get(node->right, k);
    }
}

TEST_NODE_S* get(BST_ROOT_S* root, key_type k)
{
    return _get(root->node, k);
}

BST_NODE_S* _put(BST_NODE_S* node, key_type k, value_type v)
{
    TEST_NODE_S* tmpNode = NULL;
    int cmp = 0;

    if (NULL == node)
    {
        tmpNode = (TEST_NODE_S*)malloc(sizeof(TEST_NODE_S));
        if (NULL == tmpNode)
        {
            return NULL;
        }

        tmpNode->key = k;
        tmpNode->value = v;
        tmpNode->bNode.cnt = 1;
        tmpNode->bNode.left = NULL;
        tmpNode->bNode.right = NULL;

        return &(tmpNode->bNode);
    }

    tmpNode = list_entry(node, TEST_NODE_S, bNode);
    cmp = compareTo(k, tmpNode->key);
    if (cmp < 0)
    {
        node->left = _put(node->left, k, v);
    }
    else if (cmp > 0)
    {
        node->right = _put(node->right, k, v);
    }
    else
    {
        tmpNode->value = v;
    }

    node->cnt = size(node->left) + size(node->right) + 1;
    return node;
}

void put(BST_ROOT_S* root, key_type k, value_type v)
{
    root->node = _put(root->node, k, v);
}

BST_NODE_S* _min(BST_NODE_S* node)
{
    while (NULL != node->left)
    {
        node = node->left;
    }

    return node;
}

TEST_NODE_S* min(BST_ROOT_S* root)
{
    TEST_NODE_S* tmpTestNode = NULL;
    BST_NODE_S* tmpBstNode = NULL;

    if (NULL == root)
    {
        return NULL;
    }

    tmpBstNode = root->node;

    while (NULL != tmpBstNode->left)
    {
        tmpBstNode = tmpBstNode->left;
    }

    tmpTestNode = list_entry(tmpBstNode, TEST_NODE_S, bNode);

    return tmpTestNode;
}

BST_NODE_S* _floor(BST_NODE_S* node, key_type k)
{
    TEST_NODE_S* tmpTestNode = NULL;
    BST_NODE_S* tmpBstNode = NULL;
    int cmp = 0;

    if (NULL == node)
    {
        return NULL;
    }

    tmpTestNode = list_entry(node, TEST_NODE_S, bNode);
    cmp = compareTo(k, tmpTestNode->key);

    if (0 == cmp)
    {
        return node;
    }
    else if (cmp < 0)
    {
        return _floor(node->left, k);
    }
    else
    {
        tmpBstNode = _floor(node->right, k);
        if (NULL != tmpBstNode)
        {
            return tmpBstNode;
        }
        else
        {
            return node;
        }
    }
}

TEST_NODE_S* floor(BST_ROOT_S* root, key_type k)
{
    TEST_NODE_S* tmpTestNode = NULL;
    BST_NODE_S* tmpBstNode = NULL;

    if (NULL == root)
    {
        return NULL;
    }

    tmpBstNode = _floor(root->node, k);
    if (NULL == tmpBstNode)
    {
        return NULL;
    }

    tmpTestNode = list_entry(tmpBstNode, TEST_NODE_S, bNode);
    return tmpTestNode;
}

BST_NODE_S* _select(BST_NODE_S* node, size_type k)
{
    size_type t = 0;

    if (NULL == node)
    {
        return NULL;
    }

    t = size(node->left);
    if (t > k)
    {
        return _select(node->left, k);
    }
    else if (t < k)
    {
        return _select(node->right, k - t - 1);
    }
    else
    {
        return node;
    }
}

/* 选择排名为k的节点 */
TEST_NODE_S* select(BST_ROOT_S* root, size_type k)
{
    TEST_NODE_S* tmpTestNode = NULL;
    BST_NODE_S* tmpBstNode = NULL;

    if (NULL == root)
    {
        return NULL;
    }

    tmpBstNode = _select(root->node, k);
    if (NULL == tmpBstNode)
    {
        return NULL;
    }

    tmpTestNode = list_entry(tmpBstNode, TEST_NODE_S, bNode);
    return tmpTestNode;
}

size_type _rank(BST_NODE_S* node, key_type k)
{
    TEST_NODE_S* tmpTestNode = NULL;

    int cmp = 0;

    if (NULL == node)
    {
        return 0;
    }

    tmpTestNode = list_entry(node, TEST_NODE_S, bNode);
    cmp = compareTo(k, tmpTestNode->key);
    if (cmp < 0)
    {
        return _rank(node->left, k);
    }
    else if (cmp > 0)
    {
        return 1 + size(node->left) + _rank(node->right, k);
    }
    else
    {
        return size(node->left);
    }
}

size_type rankNode(BST_ROOT_S* root, key_type k)
{
    if (NULL == root)
    {
        return 0;
    }

    return _rank(root->node, k);
}

BST_NODE_S* _deleteMin(BST_NODE_S* node)
{
    TEST_NODE_S* tmpTestNode = NULL;
    BST_NODE_S* tmpBstNode = NULL;

    if (NULL == node->left)
    {
        tmpBstNode = node->right;
        tmpTestNode = list_entry(node, TEST_NODE_S, bNode);
        if (NULL != tmpTestNode)
        {
            free(tmpTestNode);
        }

        return tmpBstNode;
    }

    node->left = _deleteMin(node->left);
    node->cnt = size(node->left) + size(node->right) + 1;
    return node;
}

void deleteMin(BST_ROOT_S* root)
{
    if (NULL == root)
    {
        return;
    }

    root->node = _deleteMin(root->node);
}

BST_NODE_S* _delete(BST_NODE_S* node, key_type k)
{
    TEST_NODE_S* tmpTestNode = NULL;
    TEST_NODE_S* newTestNode = NULL;
    BST_NODE_S* tmpBstNode = node;
    BST_NODE_S* newBstNode = NULL;
    int cmp = 0;

    if (NULL == node)
    {
        return NULL;
    }

    tmpTestNode = list_entry(node, TEST_NODE_S, bNode);
    cmp = compareTo(k, tmpTestNode->key);

    if (0 == cmp)
    {
        if (NULL == node->left)
        {
            newBstNode = node->right;
            free(tmpTestNode);
            return newBstNode;
        }

        if (NULL == node->right)
        {
            newBstNode = node->left;
            free(tmpTestNode);
            return newBstNode;
        }

        newBstNode = _min(node->right);
        newTestNode = list_entry(newBstNode, TEST_NODE_S, bNode);

        tmpTestNode->key = newTestNode->key;
        tmpTestNode->value = newTestNode->value;

        tmpBstNode->right = _deleteMin(tmpBstNode->right);
    }
    else if (cmp < 0)
    {
        node->left = _delete(node->left, k);
    }
    else
    {
        node->right = _delete(node->right, k);
    }

    node->cnt = size(node->left) + size(node->right) + 1;
    return tmpBstNode;
}

void deleteNode(BST_ROOT_S* root, key_type k)
{
    if (NULL == root)
    {
        return;
    }

    root->node = _delete(root->node, k);
    return;
}

void printForEach(BST_NODE_S* node)
{
    TEST_NODE_S* tmpTestNode = NULL;

    if (NULL == node)
    {
        return;
    }

    tmpTestNode = list_entry(node, TEST_NODE_S, bNode);
    printForEach(node->left);
    std::cout << tmpTestNode->key << std::endl;
    printForEach(node->right);
}
