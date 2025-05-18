#ifndef JOCOA_HPP
#define JOCOA_HPP

#include "./../Log/Logger.hpp"
#include <string>
#include <vector>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
    #define CP_SEPARATOR ';'
    #include <windows.h>
    #include <Lmcons.h>
    #include <codecvt>
#elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
    #define CP_SEPARATOR ':'
    #include <unistd.h>
#endif

using std::string;
using std::vector;

class Jocoa
{
public:
    static string version;
    static void init(string args[]);
    static void _help(string args[]);
    static void _new(string args[]);
    static void _search(string args[]);
    static void _run(string args[]);
    static void _clean(string args[]);
    static void _package(string args[]);
};

#endif