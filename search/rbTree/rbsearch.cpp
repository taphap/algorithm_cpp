// rbsearch.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

using std::cout;
using std::endl;
struct rb_root g_root;

int main()
{
    TEST_NODE_S* tmpNode = NULL;
    size_type rk = 0;
    g_root.rb_node = NULL;
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

    cout << "for each" << endl;
    printForEach(&g_root);

    deleteNode(&g_root, 5);
    deleteNode(&g_root, 8);
    deleteNode(&g_root, 9);
    deleteNode(&g_root, 11);
    deleteNode(&g_root, 6);
    cout << "for each" << endl;
    printForEach(&g_root);
    cout << "destory tree" << endl;
    destoryTree(&g_root);
    if (RB_EMPTY_ROOT(&g_root))
    {
        cout << "empty tree" << endl;
    }
    return 0;
}
