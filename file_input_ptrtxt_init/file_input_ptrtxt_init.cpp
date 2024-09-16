#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../onegin.h"
#include "../useful/useful.h"
#include "../file_input_ptrtxt_init/file_input_ptrtxt_init.h"

static Line* initializeLines(char* text, const int line_amount);
static void fillPtrTxt(PtrTxt* ptr_txt, char* text);
static int countLines(const char* text);

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

static Line* initializeLines(char* text, const int line_amount){
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

static void fillPtrTxt(PtrTxt* ptr_txt, char* text){
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

static int countLines(const char* text){
    assert(text);

    int line_amount = 0;
    while (*text != '\0'){
        text = strchr(text, '\n') + 1;
        line_amount++;
    }
    return line_amount;
}
