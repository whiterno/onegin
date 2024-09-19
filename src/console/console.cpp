#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "console.h"

static int processArgs(int* flag);

int checkArg(const int argc, const char* argv[], int* flag, char* file_name){
    assert(argv);
    assert(flag);

    if (argc == 1){
        return NO_FLAG;
    }

    for (int arg = 1; arg < argc; arg++){
        if (strcmp(argv[arg], "--help") == 0){
            if (*flag == NO_FLAG){
                *flag = HELP;
                continue;
            }
            else {
                *flag = TERMINAL_ERROR;
                break;
            };
        }
        if (strcmp(argv[arg], "-f") == 0){
            if (arg + 1 == argc){
                *flag = TERMINAL_ERROR;
                break;
            }
            strcpy(file_name, argv[arg + 1]);
            arg++;
            continue;
        }
        *flag = TERMINAL_ERROR;
        break;
    }

    processArgs(flag);

    return *flag;
}

static int processArgs(int* flag){
    switch(*flag){
        case TERMINAL_ERROR:{
            printf("You've made something silly, try again later\n");
            return TERMINAL_ERROR;
        }
        case NO_FLAG:{
            return NO_FLAG;
        }
        case HELP:{
            printf("\t./a.out  -  for standard read from onegin.txt from onegin folder\n");
            printf("\t./a.out -f [FILENAME]  -  for reading from your own file\n");
            return TERMINAL_ERROR;
        }
        case FILE_INPUT:{
            return NO_FLAG;
        }
    }
    printf("Unknowm ERROR occured!\n");
    return TERMINAL_ERROR;
}
