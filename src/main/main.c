#include <stdio.h>
#include <string.h>
#include "./../jocoa/jocoa.h"
#include "./../utils/str_utils.h"

typedef struct hash_element
{
    const char key[JOCOA_TOTAL_COMMAND_ALIASES][JOCOA_COMMAND_SIZE];
    void (*pair)(JOCOA_COMMAND_ARGS);
} hash_element_t;

const hash_element_t command_map[JOCOA_TOTAL_COMMANDS] = {
    {.key = {"init"}, .pair = &init},
    {.key = {"new"}, .pair = &_new},
    {.key = {"search"}, .pair = &search},
    {.key = {"run"}, .pair = &run},
    {.key = {"clean"}, .pair = &clean},
    {.key = {"build"}, .pair = &build},
    
    {.key = {"--version", "-version", "--v", "-v"}, .pair = &version},
    {.key = {"--help", "-help", "--h", "-h"}, .pair = &help},
    {.key = {"--info", "-info", "--i", "-i"}, .pair = &info},
};

int main(int argc, const char* argv[])
{
    // set logger to verbose

    // init jocoa

    if (argc < 2)
    {
        // help command
        help(argc, argv);
        return 0;
    }

    // run function mapped to command
    for (unsigned char i = 0; i < JOCOA_TOTAL_COMMANDS; i++)
    {
        for (unsigned char j = 0; j < JOCOA_TOTAL_COMMAND_ALIASES; j++)
        {
            if (strcmp(argv[1], command_map[i].key[j]) == 0) { command_map[i].pair(argc, argv); }
        }
        
    }

    return 0;
}