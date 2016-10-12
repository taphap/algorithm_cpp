#include <stdio.h>
#include "stdafx.h"
#include "binaryST.h"

size_type size(BST_NODE_S* node)
{
    if (NULL == node)
    {
        return 0;
    }

    return node->cnt;
}
