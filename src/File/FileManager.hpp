#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include "./../Macros/Macros.hpp"
#include <fstream>

using std::string;
using std::vector;
namespace fs = std::filesystem;

class FileManager
{
private:
    static string newPath;
public:
    static string currentPath;
    static void setCurrentPath();
    static void createDirectory(string path);
    static void clearDirectory(string path);
    static void remove(string path);
    static void createFile(string path);
    static void writeFile(string path, string contents);
    static bool exists(string path);
    static void standardisePath(string& path);
    static void localisePath(string& path);
    static void simplifyPath(string& path);
    static string simplifyPathNew(string& path);
    static void searchForFiles(string path, string filetype, vector<string>& jsonArray);
    static string getSystemUser();
};

#endif