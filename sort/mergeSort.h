#pragma once
#include "utility.h"

/* 归并排序，递归方式，自顶向下 */
void mergeSort(item_type a[MAX_SIZE]);

/* 归并排序，非递归，自底向上 */
void mergeSortBU(item_type a[MAX_SIZE]);