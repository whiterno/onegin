#include <assert.h>
#include <stdio.h>
#include "../onegin.h"
#include "../sort/sort.h"

static void fputsUntilNewline(const char* ptr, FILE* fp);
static void fprintTxt(const PtrTxt ptr_txt, FILE* fp);
static void fprintLine(FILE* fp);

static void fputsUntilNewline(const char* ptr, FILE* fp){
    size_t amount = 0;

    do{
        fputc(*(ptr + amount), fp);
    }while (*(ptr + amount++) != '\n');
}

static void fprintTxt(const PtrTxt ptr_txt, FILE* fp){
    assert(fp);

    for (int i = 0; i < ptr_txt.line_amount; i++){
        if (*ptr_txt.ptr_array[i].ptr_line != '\n'){
            fputsUntilNewline(ptr_txt.ptr_array[i].ptr_line, fp);
        }
    }
}

static void fprintLine(FILE* fp){
    fputc('\n', fp);
    fputsUntilNewline(LINE, fp);
    fputc('\n', fp);
}

void sortPrint(PtrTxt ptr_txt, cmp_t compare, FILE* fp, int sort_type){
    if (sort_type == MY_QSORT){
        quickSort(ptr_txt.ptr_array, sizeof(Line), 0, ptr_txt.line_amount - 1, compare);
    }
    else{
        qsort(ptr_txt.ptr_array, ptr_txt.line_amount, sizeof(Line), compare);
    }
    fprintTxt(ptr_txt, fp);

    fprintLine(fp);
}
