#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./../macros/macros.h"

void str_split(char str[], const char* delimiter, char* output[], const size_t occurences, size_t* count);
char* str_remove(char str[], const char* token, const size_t occurences);
char* str_replace(char str[], const char* find, const char* replace, const size_t occurences);
char* str_replace_char(char str[], const char find, const char replace, const size_t occurences);

#endif