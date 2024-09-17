#include <ctype.h>
#include <assert.h>
#include "../comparators/comparators.h"
#include "../onegin.h"

int myLinecmp(const void* line1, const void* line2){
    assert(line1);
    assert(line2);

    char* str1 = ((Line*)line1)->ptr_line + ((Line*)line1)->skip_length;
    char* str2 = ((Line*)line2)->ptr_line + ((Line*)line2)->skip_length;
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


int myLinecmpRev(const void* line1, const void* line2){
    assert(line1);
    assert(line2);

    int length1 = ((Line*)line1)->length - ((Line*)line1)->skip_length_end + 1;
    int length2 = ((Line*)line2)->length - ((Line*)line2)->skip_length_end + 1;

    char* str1 = ((Line*)line1)->ptr_line + length1 - 1;
    char* str2 = ((Line*)line2)->ptr_line + length2 - 1;

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
