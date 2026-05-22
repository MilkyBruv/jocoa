#include "file_manager.h"

void createDirectory(char* path)
{
    char* folders[JOCOA_MAX_PATH];
    str_split(&path, JOCOA_OS_SEP, folders, JOCOA_MAX_PATH);
    bool success;
    char* log_str;
    char* current_path;

    size_t path_start = path[0] == '.' ? 1 : 0;

    for (size_t i = path_start; i < JOCOA_MAX_PATH; i++)
    {
        success = false;

        #if defined(_WIN32) || defined(_WIN64)
            success = CreateDirectory(path, NULL);
        #elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
            // returns 0 for pass, -1 for fail, so + 1 is 0 (false) and 1 (true)
            success = (bool) (mkdir(path, 0777) + 1);
        #endif

        if (success)
        {
            log_str = strcat("Created ", path);
            logger_info(log_str);
        }
        else
        {
            log_str = strcat("Failed to create ", path);
            logger_error(log_str);
        }
    }

    
}

void standardisePath(char *path)
{
    #if defined(_WIN32) || defined(_WIN64)
        // 
    #elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
        // 
    #endif
}
