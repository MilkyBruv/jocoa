#ifndef MACROS_H
#define MACROS_H

#if defined(_WIN32) || defined(_WIN64)
    #define JOCOA_OS_SEP ';'
    #include <Windows.h>
#elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
    #define JOCOA_OS_SEP ':'
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

#define JOCOA_MAX_PATH 32
#define JOCOA_MAX_SPLIT 32

#endif