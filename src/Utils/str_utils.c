#include "str_utils.h"

void split_string(char* str, const char* delimiter, char** output, size_t max_out)
{   
    if (max_out == 0) { return; }

    char* token = strtok(str, delimiter);
    printf("token: %s\n", token);
    size_t i = 0;

    while (token != NULL && i < max_out)
    {
        output[i] = token;
        printf("toke: %s\n", token);
        token = strtok(NULL, delimiter);
        i++;
    }
}