#include "file_manager.h"

void create_directory(char path[])
{
    char* folders[JOCOA_MAX_PATH];

    // Standardise path for current os
    char* new_path = standardise_path(path);

    // Split folders
    size_t count;
    str_split(new_path, JOCOA_OS_SEP_STR, folders, JOCOA_MAX_PATH, &count);

    int success;
    char log_str[256];
    char current_path[256] = ".";

    // Loop through each folder and create each one
    for (size_t i = 0; i < count; i++)
    {
        success = 0;

        // Skip "../" and "./"
        if (strcmp(folders[i], "..") == 0 || strcmp(folders[i], ".") == 0) { continue; }

        // Append next folder to current_path
        strcat(current_path, JOCOA_OS_SEP_STR);
        strcat(current_path, folders[i]);

        // Create current_path
        #if defined(_WIN32) || defined(_WIN64)
            success = CreateDirectory(current_path, NULL);
        #elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
            // returns 0 for pass, -1 for fail, so + 1 is 0 (false) and 1 (true)
            success = (bool) (mkdir(current_path, 0777) + 1);
        #endif

        if (success > 0)
        {
            sprintf(log_str, "Created %s", current_path);
            logger_info(log_str);
        }
        else
        {
            sprintf(log_str, "Failed to create %s", current_path);
            logger_error(log_str);
        }

        printf("post POST check\n");
    }
}

void clear_directory(char path[])
{
    
}

char* standardise_path(char path[])
{
    #if defined(_WIN32) || defined(_WIN64)
        return str_replace_char(path, '/', JOCOA_OS_SEP, JOCOA_MAX_PATH);
    #elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
        return str_replace_char(path, '\\', JOCOA_OS_SEP, JOCOA_MAX_PATH);
    #endif
}
