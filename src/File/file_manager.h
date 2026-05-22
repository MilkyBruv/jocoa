#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdbool.h>
#include "macros.h"
#include "logger.h"
#include "str_utils.h"

void createDirectory(char* path);
void clearDirectory(char* path);
void remove(char* path);
void createFile(char* path);
void writeFile(char* path, char* contents);
bool exists(char* path);
void standardisePath(char* path);
void localisePath(char* path);
void simplifyPath(char* path);
char* simplifyPathNew(char* path);
void searchForFiles(char* path, char* filetype, char* jsonArray[]);
char* getSystemUser();

#endif