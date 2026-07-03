#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdbool.h>
#include "./../macros/macros.h"
#include "./../log/logger.h"
#include "./../utils/str_utils.h"

/// @brief Creates the specified directory split by `/` or `\`
/// @param path The path to create
void create_directory(char path[]);
/// @brief Clears the specified directory of all files and folders
/// @param path The path to clear
void clear_directory(char path[]);
// void remove(char* path);
void createFile(char* path);
void writeFile(char* path, char* contents);
bool exists(char* path);
char* standardise_path(char path[]);
void localisePath(char* path);
void simplifyPath(char* path);
char* simplifyPathNew(char* path);
void searchForFiles(char* path, char* filetype, char* jsonArray[]);
char* getSystemUser();

#endif