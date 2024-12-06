#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include <stdio.h>

#include "../onegin.h"
#include "../sort/sort.h"

inline static size_t min(size_t num1, size_t num2);
inline static void swapElements(void* ptr_array, const size_t size_el, const size_t inx1, const size_t inx2);
inline static void swapElementsStd(void* ptr_array, size_t size_el, const size_t inx1, const size_t inx2);

static void* tmp = (void*)calloc(1, PAGE_SIZE);

inline static size_t min(size_t num1, size_t num2){
    return (num1 > num2) ? num2 : num1;
}

inline static void swapElements(void* ptr_array, const size_t size_el, const size_t inx1, const size_t inx2){
    assert(ptr_array);

    size_t copy_amount = (size_el % PAGE_SIZE == 0)? size_el / PAGE_SIZE - 1 : size_el / PAGE_SIZE;
    size_t add = PAGE_SIZE * copy_amount;
    for (size_t copy_iter = 0; copy_iter < copy_amount; copy_iter++){
        size_t add_for = PAGE_SIZE * copy_iter;

        memcpy(tmp, (char*)ptr_array + inx1 * size_el + add_for, PAGE_SIZE);
        memcpy((char*)ptr_array + inx1 * size_el + add_for, (char*)ptr_array + inx2 * size_el + add_for, PAGE_SIZE);
        memcpy((char*)ptr_array + inx2 * size_el + add_for, tmp, PAGE_SIZE);
    }

    memcpy(tmp, (char*)ptr_array + inx1 * size_el + add, size_el);
    memcpy((char*)ptr_array + inx1 * size_el + add, (char*)ptr_array + inx2 * size_el + add, size_el);
    memcpy((char*)ptr_array + inx2 * size_el + add, tmp, size_el);
}

inline static void swapElementsStd(void* ptr_array, size_t size_el, const size_t inx1, const size_t inx2){
    char* ptr_inx1 = (char*)ptr_array + inx1 * size_el;
    char* ptr_inx2 = (char*)ptr_array + inx2 * size_el;
    while (size_el > 0){
        size_t block = min(PAGE_SIZE, size_el);

        memcpy(tmp, ptr_inx1, block);
        memcpy(ptr_inx1, ptr_inx2, block);
        memcpy(ptr_inx2, tmp, block);

        ptr_inx1 += block;
        ptr_inx2 += block;
        size_el -= block;
    }
}

void quickSort(void* ptr_array, const size_t size_el, const int start, const int end, const cmp_t compare, size_t recursion_depth){
    assert(ptr_array);

    if (start < end){
        int left = start, right = end;
        int middle = (left + right) / 2;

        while(left <= right){
            while (compare((char*)ptr_array + left * size_el, (char*)ptr_array + middle * size_el) < 0){
                left++;
            }
            while (compare((char*)ptr_array + right * size_el, (char*)ptr_array + middle * size_el) > 0){
                right--;
            }
            if (left <= right){
                swapElementsStd(ptr_array, size_el, left, right);
                left++;
            }
        }
        quickSort(ptr_array, size_el, start, right, compare, recursion_depth + 1);
        quickSort(ptr_array, size_el, left, end, compare, recursion_depth + 1);
    }

    if (recursion_depth == 0){
        free(tmp);
        tmp = NULL;
    }
}
