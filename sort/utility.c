#include "utility.h"

bool little(item_type a, item_type b)
{
    if (a < b)
    {
        return true;
    }

    return false;
}

void exch(item_type* a, item_type* b)
{
    item_type tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;

    return;
}