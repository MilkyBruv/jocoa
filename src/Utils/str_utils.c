#include "str_utils.h"

void str_split(char (*str)[], const char* delimiter, char* output[], size_t max_out)
{   
    size_t len = sizeof(*output) / sizeof(output[0]);

    if (max_out > len) { max_out = len; }
    if (max_out == 0) { return; }

    char* token = strtok(*str, delimiter);
    size_t i = 0;

    while (token != NULL && i < max_out)
    {
        output[i++] = token;
        token = strtok(NULL, delimiter);
    }
}

void str_remove(char* str, const char* token, const size_t occurences)
{
    char* splits[JOCOA_MAX_SPLIT];
}

void str_replace(char (*str)[], const char *find, const char *replace)
{
}
