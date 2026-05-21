#ifndef JOCOA_H
#define JOCOA_H

#include <stdio.h>

// #include "./../Log/Logger.hpp"
// #include "./../File/FileManager.hpp"
// #include "./../Json/JsonManager.hpp"
// #include "./../Command/CommandBuilder.hpp"

#define JOCOA_COMMAND_ARGS int argc, const char* argv[]

void init(JOCOA_COMMAND_ARGS);
void help(JOCOA_COMMAND_ARGS);
void info(JOCOA_COMMAND_ARGS);
void _new(JOCOA_COMMAND_ARGS);
void search(JOCOA_COMMAND_ARGS);
void run(JOCOA_COMMAND_ARGS);
void clean(JOCOA_COMMAND_ARGS);
void build(JOCOA_COMMAND_ARGS);

#endif