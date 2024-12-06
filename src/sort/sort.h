#ifndef SORT_HEADER
#define SORT_HEADER

#include "../onegin.h"

const int PAGE_SIZE = 4096;

void quickSort(void* ptr_array, const size_t size_el, const int start, const int end, const cmp_t compare, size_t recursion_depth);

#endif
