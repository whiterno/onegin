#ifndef USEFUL_HEADER
#define USEFUL_HEADER

#include "../onegin.h"

void freeAll(char* text, PtrTxt* ptr_txt);
size_t fileSize(const char* filename);
void putsUntilNewline(const char* ptr);
int skipTypoSymbols(const char* string, const int step, int length);

#endif
