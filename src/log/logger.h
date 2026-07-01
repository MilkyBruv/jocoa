#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>

extern bool verbose;

void logger_set_verbose(bool state);
void logger_info(char* msg);
void logger_warn(char* msg);
void logger_error(char* msg);

#endif