#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "macros.h"

void str_split(char (*str)[], const char* delimiter, char* output[], const size_t max_out);
void str_remove(char* str, const char* token, const size_t occurences);
void str_replace(char (*str)[], const char* find, const char* replace);

#endif