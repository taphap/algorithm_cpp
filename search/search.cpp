// search.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "binarySTSample.h"
using namespace std;

BST_ROOT_S g_root;

int main()
{
    TEST_NODE_S* tmpNode = NULL;
    size_type rk = 0;
    g_root.node = NULL;
    put(&g_root, 9, 9);
    put(&g_root, 5, 5);
    put(&g_root, 13, 13);
    put(&g_root, 3, 3);
    put(&g_root, 8, 8);
    put(&g_root, 11, 11);
    put(&g_root, 6, 6);
    
    cout << "test get" << endl;
    tmpNode = get(&g_root, 5);
    cout << tmpNode->value << endl;
    tmpNode = get(&g_root, 6);
    cout << tmpNode->value << endl;
    tmpNode = get(&g_root, 9);
    cout << tmpNode->value << endl;

    cout << "test min" << endl;
    tmpNode = min(&g_root);
    cout << tmpNode->value << endl;

    cout << "test floor" << endl;
    tmpNode = floor(&g_root, 10);
    cout << tmpNode->value << endl;
    tmpNode = floor(&g_root, 7);
    cout << tmpNode->value << endl;
    tmpNode = floor(&g_root, 4);
    cout << tmpNode->value << endl;
    tmpNode = floor(&g_root, 13);
    cout << tmpNode->value << endl;
    tmpNode = floor(&g_root, 3);
    cout << tmpNode->value << endl;

    cout << "select" << endl;
    tmpNode = select(&g_root, 0);
    cout << tmpNode->value << endl;
    tmpNode = select(&g_root, 1);
    cout << tmpNode->value << endl;
    tmpNode = select(&g_root, 2);
    cout << tmpNode->value << endl;
    tmpNode = select(&g_root, 6);
    cout << tmpNode->value << endl;

    cout << "rank" << endl;
    cout << rankNode(&g_root, 3) << endl;
    cout << rankNode(&g_root, 5) << endl;
    cout << rankNode(&g_root, 6) << endl;
    cout << rankNode(&g_root, 8) << endl;
    cout << rankNode(&g_root, 9) << endl;
    cout << rankNode(&g_root, 11) << endl;
    cout << rankNode(&g_root, 13) << endl;

    deleteMin(&g_root);
    deleteNode(&g_root, 5);
    deleteNode(&g_root, 8);
    deleteNode(&g_root, 9);
    deleteNode(&g_root, 11);
    deleteNode(&g_root, 6);
    deleteNode(&g_root, 13);
    cout << "for each" << endl;
    printForEach(g_root.node);
    return 0;
}

