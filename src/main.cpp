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
#include "console/console.h"
#include "onegin.h"

int main(const int argc, const char* argv[]){
    char * text = NULL;
    char file_input[MAX_FILENAME_SIZE];
    strcpy(file_input, FILENAME);
    int flag = NO_FLAG;
    FILE* fp = fopen(FILENAME_OUT, "w");
    PtrTxt ptr_txt = {.ptr_array = NULL, .line_amount = 0};

    checkArg(argc, argv, &flag, file_input);

    text = readFile(&ptr_txt, file_input);

    sortPrint(ptr_txt, myLinecmp, fp, STANDART_QSORT);
    sortPrint(ptr_txt, myLinecmpRev, fp, MY_QSORT);
    fputs(text, fp);

    fclose(fp);
    freeAll(text, &ptr_txt);
    text = NULL;

    return 0;
}
