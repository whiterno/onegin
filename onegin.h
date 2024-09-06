#ifndef ONEGIN_HEADER
#define ONEGIN_HEADER

struct PtrTxt{
    char ** ptr_array;
    int * skip_length;
    int line_amount;
};

const char FILENAME[] = "./onegin";
const char FILENAME_OUT[] = "./onegin_sorted";
const char LINE[] = "--------------------------------------------------------------\n";
const int MAX_READ_LENGTH = 100;

int myStrcmp(const char* str1, const char* str2, const int* add_array, const int inx);
size_t fileSize(const char* filename);
char* readFile(PtrTxt * ptr_txt);
char ** makePtrArray(char* text, const int line_amount);
void putsUntilNewline(const char* ptr);
void fputsUntilNewline(const char* ptr, FILE* fp);
void swapPointers(char ** ptr1, char** ptr2);
void swapAdds(int* num1, int* num2);
void bubbleSort(PtrTxt* ptr_txt);

#endif
