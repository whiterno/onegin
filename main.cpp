#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "onegin.h"

int main(void){
    char * text = NULL;
    FILE* fp = fopen(FILENAME_OUT, "w");
    PtrTxt ptr_txt = {.ptr_array = NULL, .line_amount = 0};

    text = readFile(&ptr_txt);

    sortPrint(ptr_txt, myLinecmp, fp);
    sortPrint(ptr_txt, myLinecmpRev, fp);
    fputs(text, fp);

    fclose(fp);
    freeAll(text, &ptr_txt);
}

int myLinecmp(const Line line1, const Line line2){
    char* str1 = line1.ptr_line + line1.skip_length;
    char* str2 = line2.ptr_line + line2.skip_length;
    while (*str1 != '\n' && *str2 != '\n'){
        if (tolower(*str1 ) - tolower(*str2) != 0){
            return tolower(*str1) - tolower(*str2);
        }
        str1++;
        str2++;
    }
    if (*str1 == '\n' && *str2 == '\n'){
        return 0;
    }
    if (*str1 == '\n'){
        return -*str2;
    }
    return *str1;
}

int myLinecmpRev(const Line line1, const Line line2){
    int length1 = line1.length - line1.skip_length_end + 1;
    int length2 = line2.length - line2.skip_length_end + 1;

    char* str1 = line1.ptr_line + length1 - 1;
    char* str2 = line2.ptr_line + length2 - 1;

    while(length1 > 0 && length2 > 0){
        if (tolower(*str1) - tolower(*str2) != 0){
            return tolower(*str1) - tolower(*str2);
        }
        str1--;
        str2--;
        length1--;
        length2--;
    }
    if (length1 == 0 && length2 == 0){
        return 0;
    }
    if (length1 == 0){
        return -*str2;
    }
    return *str1;
}

size_t fileSize(const char* filename){
    assert(filename);

    struct stat file_stat;
    stat(filename, &file_stat);
    return file_stat.st_size;
}

char* readFile(PtrTxt * ptr_txt){
    assert(ptr_txt);

    size_t fsize = fileSize(FILENAME);
    char* text = (char*)calloc(fsize + 2, sizeof(char));
    int fp = open(FILENAME, O_RDONLY);

    read(fp, text, fsize);
    close(fp);

    text[fsize] = '\n';
    text[fsize + 1] = '\0';

    ptr_txt->line_amount = countLines(text);
    fillPtrTxt(ptr_txt, text);

    return text;
}

Line* initializeLines(char* text, const int line_amount){
    assert(text);

    int line = 0;
    Line* ptr_arr = (Line*)calloc(line_amount, sizeof(Line));

    while (*text != '\0'){
        int length = (int)(strchr(text, '\n') - text);

        (ptr_arr + line)->ptr_line = text;
        (ptr_arr + line)->length = length;
        text += length + 1;
        line++;
    }

    return ptr_arr;
}

void putsUntilNewline(const char* ptr){
    size_t amount = 0;

    do{
        putchar(*(ptr + amount));
    }while (*(ptr + amount++) != '\n');
}

void fputsUntilNewline(const char* ptr, FILE* fp){
    size_t amount = 0;

    do{
        fputc(*(ptr + amount), fp);
    }while (*(ptr + amount++) != '\n');
}

void swapLines(Line* ptr_array, int inx1, int inx2){
    assert(ptr_array);

    Line tmp_line = ptr_array[inx1];
    ptr_array[inx1] = ptr_array[inx2];
    ptr_array[inx2] = tmp_line;
}

void bubbleSort(Line* ptr_array, int line_amount, cmp_t compare){
    assert(ptr_array);

    for (int i = 0; i < line_amount - 1; i++){
        for (int j = 0; j < line_amount - 1 - i; j++){
            if (compare(ptr_array[j], ptr_array[j + 1]) > 0){
                swapLines(ptr_array, j, j + 1);
            }
        }
    }
}

int skipTypoSymbols(char* string, int step, int length){
    assert(string);

    int amount = 0;

    while (true){
        if (length-- && ((*string < 'A') || (*string > 'Z' && *string < 'a') || (*string > 'z'))){
            amount++;
            string += step;
            continue;
        }
        break;
    }

    return amount;
}

void fillPtrTxt(PtrTxt* ptr_txt, char* text){
    assert(text);
    assert(ptr_txt);

    ptr_txt->ptr_array = initializeLines(text, ptr_txt->line_amount);

    for (int i = 0; i < ptr_txt->line_amount; i++){
        (ptr_txt->ptr_array + i)->skip_length = skipTypoSymbols(ptr_txt->ptr_array[i].ptr_line, 1, ptr_txt->ptr_array[i].length);
    }
    for (int i = 0; i < ptr_txt->line_amount; i++){
        char* end_line = ptr_txt->ptr_array[i].ptr_line + ptr_txt->ptr_array[i].length;
        (ptr_txt->ptr_array + i)->skip_length_end = skipTypoSymbols(end_line, -1, ptr_txt->ptr_array[i].length);
    }
}

void quickSort(Line* ptr_array, int start, int end, cmp_t compare){
    assert(ptr_array);

    if (start < end){
        int left = start, right = end;
        int middle = (left + right) / 2;
        Line middle_el = ptr_array[middle];

        while(left <= right){
            while (compare(ptr_array[left], middle_el) < 0){
                left++;
            }
            while (compare(ptr_array[right], middle_el) > 0){
                right--;
            }
            if (left <= right){
                swapLines(ptr_array, left, right);
                left++;
                right--;
            }
        }
        quickSort(ptr_array, start, right, compare);
        quickSort(ptr_array, left, end, compare);
    }
}

int countLines(char* text){
    assert(text);

    int line_amount = 0;
    while (*text != '\0'){
        text = strchr(text, '\n') + 1;
        line_amount++;
    }
    return line_amount;
}

void fprintTxt(PtrTxt ptr_txt, FILE* fp){
    assert(fp);

    for (int i = 0; i < ptr_txt.line_amount; i++){
        if (*ptr_txt.ptr_array[i].ptr_line != '\n'){
            fputsUntilNewline(ptr_txt.ptr_array[i].ptr_line, fp);
        }
    }
}

void freeAll(char* text, PtrTxt* ptr_txt){
    assert(text);
    assert(ptr_txt);

    for (int i = 0; i < ptr_txt->line_amount; i++){
        ptr_txt->ptr_array[i].ptr_line = NULL;
    }

    free(ptr_txt->ptr_array);
    free(text);
}

void fprintLine(FILE* fp){
    fputc('\n', fp);
    fputsUntilNewline(LINE, fp);
    fputc('\n', fp);
}

void sortPrint(PtrTxt ptr_txt, cmp_t compare, FILE* fp){
    quickSort(ptr_txt.ptr_array, 0, ptr_txt.line_amount - 1, compare);
    fprintTxt(ptr_txt, fp);

    fprintLine(fp);
}
