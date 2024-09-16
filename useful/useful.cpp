#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "../onegin.h"
#include "../useful/useful.h"

size_t fileSize(const char* filename){
    assert(filename);

    struct stat file_stat;
    stat(filename, &file_stat);
    return file_stat.st_size;
}

void putsUntilNewline(const char* ptr){
    size_t amount = 0;

    do{
        putchar(*(ptr + amount));
    }while (*(ptr + amount++) != '\n');
}

int skipTypoSymbols(const char* string, const int step, int length){
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

void freeAll(char* text, PtrTxt* ptr_txt){
    assert(text);
    assert(ptr_txt);

    for (int i = 0; i < ptr_txt->line_amount; i++){
        ptr_txt->ptr_array[i].ptr_line = NULL;
    }

    free(ptr_txt->ptr_array);
    free(text);
}
