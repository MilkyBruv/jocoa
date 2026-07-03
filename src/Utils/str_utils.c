#include "str_utils.h"

void str_split(char str[], const char* delimiter, char* output[], const size_t occurences, size_t* count)
{   
    if (occurences == 0) { return; }

    char* token = strtok(str, delimiter);
    size_t i = 0;

    while (token != NULL && i < occurences) // add 1 cuz need to split around delimiter
    {
        output[i++] = token;
        token = strtok(NULL, delimiter);
    }

    *count = i;
}

char* str_remove(char str[], const char* token, const size_t occurences)
{
    char* new_str = "";
    char* splits[JOCOA_MAX_SPLIT] = {NULL};
    size_t count;
    str_split(str, token, splits, occurences, &count);
    
    for (size_t i = 0; i < count; i++)
    {
        strcat(new_str, splits[i]);
    }

    return new_str;
}

char* str_replace(char str[], const char* find, const char* replace, const size_t occurences)
{
    char* splits[JOCOA_MAX_SPLIT] = {NULL};
    size_t count;
    str_split(str, find, splits, occurences, &count);

    if (splits[0] == NULL || count == 0) { return str; }

    char* new_str = splits[0];

    // Start from one cuz using splits[0] as first bit of string yk
    for (size_t i = 1; i < count; i++)
    {
        strcat(new_str, replace);
        strcat(new_str, splits[i]);
    }

    return new_str;
}

char* str_replace_char(char str[], const char find, const char replace, const size_t occurences)
{
    size_t count = 0;

    for (size_t i = 0; i < strlen(str); i++)
    {
        if (count > occurences) { break; }
        if (str[i] == find) { str[i] = replace; count++; }
    }

    return str;
}
