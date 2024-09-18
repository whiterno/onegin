#ifndef CONSOLE_HEADER
#define CONSOLE_HEADER

enum Flags{
    TERMINAL_ERROR = -1,
    NO_FLAG,
    HELP,
    FILE_INPUT
};

int checkArg(const int argc, const char* argv[], int* flag, char* file_name);

#endif
