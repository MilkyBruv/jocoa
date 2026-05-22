#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>

extern bool verbose;

static void logger_set_verbose(bool state);
static void logger_info(char* msg);
static void logger_warn(char* msg);
static void logger_error(char* msg);

#endif