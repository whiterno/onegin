#ifndef ONEGIN_HEADER
#define ONEGIN_HEADER

enum StringCmp{
    START,
    END
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

typedef int (*cmp_t)(const Line line1, const Line line2);

const char FILENAME[] = "./onegin";
const char FILENAME_OUT[] = "./onegin_sorted";
const char LINE[] = "--------------------------------------------------------------\n";
const int MAX_READ_LENGTH = 100;

int myLinecmp(const Line line1, const Line line2);
int myLinecmpRev(const Line line1, const Line line2);
size_t fileSize(const char* filename);
char* readFile(PtrTxt * ptr_txt);
Line* initializeLines(char* text, const int line_amount);
void putsUntilNewline(const char* ptr);
void fputsUntilNewline(const char* ptr, FILE* fp);
void swapLines(Line* ptr_array, int inx1, int inx2);
void bubbleSort(Line* ptr_array, int line_amount, cmp_t compare);
void quickSort(Line* ptr_array, int start, int end, cmp_t compare);
int skipTypoSymbols(char* string, int step, int length);
void fillPtrTxt(PtrTxt* ptr_txt, char* text);
int countLines(char* text);
void fprintTxt(PtrTxt ptr_txt, FILE* fp);
void freeAll(char* text, PtrTxt* ptr_txt);
void fprintLine(FILE* fp);
void sortPrint(PtrTxt ptr_txt, cmp_t compare, FILE* fp);

#endif
