#ifndef ONEGIN_HEADER
#define ONEGIN_HEADER

enum Sort{
    STANDART_QSORT,
    MY_QSORT
};

struct Line{
    char* ptr_line;
    int skip_length;
    int skip_length_end;
    int length;
};

struct PtrTxt{
    Line* ptr_array;
    int line_amount;
};

typedef int (*cmp_t)(const void* el1, const void* el2);

const char FILENAME[] = "./onegin.txt";
const char FILENAME_OUT[] = "./onegin_sorted.txt";
const char LINE[] = "--------------------------------------------------------------\n";
const int MAX_READ_LENGTH = 100;
const int MAX_FILENAME_SIZE = 256;

#endif
