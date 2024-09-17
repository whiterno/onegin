#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../onegin.h"
#include "../sort/sort.h"

inline static void swapElements(void* ptr_array, const size_t size_el, const int inx1, const int inx2);

inline static void swapElements(void* ptr_array, const size_t size_el, const int inx1, const int inx2){
    assert(ptr_array);

    void* tmp = (void*)calloc(1, size_el);

    memcpy(tmp, (char*)ptr_array + inx1 * size_el, size_el);
    memcpy((char*)ptr_array + inx1 * size_el, (char*)ptr_array + inx2 * size_el, size_el);
    memcpy((char*)ptr_array + inx2 * size_el, tmp, size_el);

    free(tmp);
}

void quickSort(void* ptr_array, const size_t size_el, const int start, const int end, const cmp_t compare){
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
                swapElements(ptr_array, size_el, left, right);
                left++;
                right--;
            }
        }
        quickSort(ptr_array, size_el, start, right, compare);
        quickSort(ptr_array, size_el, left, end, compare);
    }
}
