#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include "onegin.h"

int main(void){
    char * text;
    FILE* fp = fopen(FILENAME_OUT, "w");

    PtrTxt left_to_right = {.line_amount = 0};

    text = readFile(&left_to_right);

    bubbleSort(&left_to_right);

    for (int i = 0; i < left_to_right.line_amount; i++){
        if (*left_to_right.ptr_array[i] != '\n'){
            fputsUntilNewline(left_to_right.ptr_array[i], fp);
        }
    }

    fputc('\n', fp);
    fputsUntilNewline(LINE, fp);
    fputc('\n', fp);
}

int myStrcmp(const char* str1, const char* str2, const int* add_array, const int inx){
    assert(str1);
    assert(str2);

    int num1 = add_array[inx], num2 = add_array[inx + 1];

    str1 += num1;
    str2 += num2;


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

size_t fileSize(const char* filename){
    assert(filename);

    struct stat file_stat;
    stat(filename, &file_stat);
    return file_stat.st_size;
}

char* readFile(PtrTxt * ptr_txt){
    assert(ptr_txt);

    char* text = (char*)calloc(fileSize(FILENAME) + 1, sizeof(char));
    FILE* fp = fopen(FILENAME, "r");
    int character = 0;
    size_t amount = 0;

    while ((character = fgetc(fp))){
        if (character == EOF){
            break;
        }
        *(text + amount) = character;
        amount++;
        if (character == '\n'){
            (ptr_txt->line_amount)++;
        }
    }
    if (*(text + amount - 1) != '\n'){
        (ptr_txt->line_amount)++;
    }
    *(text + amount) = '\0';

    ptr_txt->ptr_array = makePtrArray(text, ptr_txt->line_amount);

    ptr_txt->skip_length = (int*)calloc(ptr_txt->line_amount, sizeof(int));
    for (int i = 0; i < ptr_txt->line_amount; i++){
        sscanf((ptr_txt->ptr_array)[i], "%*[!-@[-`{-~]%n", ptr_txt->skip_length + i);
    }

    return text;
}

char ** makePtrArray(char* text, const int line_amount){
    assert(text);

    size_t amount = 0;
    int line = 1;
    char ** ptr_arr = (char**)calloc(line_amount, sizeof(char*));

    *ptr_arr = text;
    while (*(text + amount) != '\0'){
        if (*(text + amount) == '\n'){
            *(ptr_arr + line) = text + amount + 1;
            line++;
        }
        amount++;
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

void swapPointers(char ** ptr1, char** ptr2){
    char* tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

void swapAdds(int* num1, int* num2){
    int tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

void bubbleSort(PtrTxt* ptr_txt){
    for (int i = 0; i < ptr_txt->line_amount - 1; i++){
        for (int j = 0; j < ptr_txt->line_amount - 1 - i; j++){
            if (myStrcmp(ptr_txt->ptr_array[j], ptr_txt->ptr_array[j + 1], ptr_txt->skip_length, j) > 0){
                swapAdds(ptr_txt->skip_length + j, ptr_txt->skip_length + j + 1);
                swapPointers(ptr_txt->ptr_array + j, ptr_txt->ptr_array + j + 1);
            }
        }
    }
}
