#ifndef MACROS_HPP
#define MACROS_HPP

#include "./../Utils/Utils.hpp"
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

#if defined(_WIN32) || defined(_WIN64)
    #define CP_SEPARATOR ';'
    #include <windows.h>
    #include <Lmcons.h>
    #include <codecvt>
#elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
    #define CP_SEPARATOR ':'
    #include <unistd.h>
#endif

#endif