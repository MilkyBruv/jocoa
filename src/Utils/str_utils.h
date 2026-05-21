#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void split_string(char* str, const char* delimiter, char** output, size_t max_out);

#endif