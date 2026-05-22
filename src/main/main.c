#include <stdio.h>
#include <string.h>
#include "./../jocoa/jocoa.h"
#include "./../utils/str_utils.h"

typedef struct hash_element
{
    const char* key;
    void (*pair)(JOCOA_COMMAND_ARGS);
} hash_element_t;

#define JOCOA_TOTAL_COMMANDS 8

const hash_element_t command_map[JOCOA_TOTAL_COMMANDS] = {
    {.key = "init",     .pair = &init},
    {.key = "help",     .pair = &help},
    {.key = "info",     .pair = &info},
    {.key = "new",      .pair = &_new},
    {.key = "search",   .pair = &search},
    {.key = "run",      .pair = &run},
    {.key = "clean",    .pair = &clean},
    {.key = "build",    .pair = &build}
};

int main(int argc, const char* argv[])
{
    // set logger to verbose

    // init jocoa

    if (argc < 2)
    {
        // help command
        return 0;
    }

    // run function mapped to command
    for (unsigned char i = 0; i < JOCOA_TOTAL_COMMANDS; i++)
    {
        if (strcmp(argv[1], command_map[i].key) == 0) { command_map[i].pair(argc, argv); }
    }

    return 0;
}