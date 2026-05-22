#include "logger.h"

bool verbose = true;

static void logger_set_verbose(bool state)
{
    verbose = state;
}

static void logger_info(char* msg)
{
    if (!verbose) { return; }
    printf("\033[32m%s\033[0m\n", msg);
}

static void logger_warn(char* msg)
{
    if (!verbose) { return; }
    printf("\033[33m%s\033[0m\n", msg);
}

static void logger_error(char* msg)
{
    if (!verbose) { return; }
    printf("\033[31m%s\033[0m\n", msg);
}
