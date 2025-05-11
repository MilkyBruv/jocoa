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

typedef struct JsonData
{
    string name;
    string type;
    string package;
    vector<string> sourceFiles;
    vector<string> dependencies;
    string natives;
} JsonData;

class Jocoa
{
private:
    static void createDirectory(string path);
    static void createFile(string path);
    static void writeFile(string path, string contents);
    static vector<string> split(string str, string delimiter);
    static void standardisePath(string& path);
    static void localisePath(string& path);
    static void simplifyPath(string& path);
    static void searchForFiles(string path, string filetype, vector<string>& jsonArray);
public:
    static string currentPath;
    static JsonData jsonData;
    static string version;
    static void init(string args[]);
    static void _help(string args[]);
    static void _new(string args[]);
    static void _search(string args[]);
    static void _run(string args[]);
    static void _clean(string args[]);
    static void _package(string args[]);
    static void _repair(string args[]);
};

#endif