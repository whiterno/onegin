#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "comparators/comparators.h"
#include "file_input_ptrtxt_init/file_input_ptrtxt_init.h"
#include "file_output/file_output.h"
#include "sort/sort.h"
#include "useful/useful.h"
#include "onegin.h"

int main(void){
    char * text = NULL;
    FILE* fp = fopen(FILENAME_OUT, "w");
    PtrTxt ptr_txt = {.ptr_array = NULL, .line_amount = 0};

    text = readFile(&ptr_txt);

    sortPrint(ptr_txt, myLinecmp, fp, STANDART_QSORT);
    sortPrint(ptr_txt, myLinecmpRev, fp, MY_QSORT);
    fputs(text, fp);

    fclose(fp);
    freeAll(text, &ptr_txt);
    text = NULL;
}
