#ifndef JOCOA_HPP
#define JOCOA_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

typedef struct Task
{
    string projectName;
    string projectType;
    vector<string> sourceFiles;
    vector<string> dependencies;
    string natives;
} Task;

class Jocoa
{
private:
    static void createDirectory(string path);
    static void createFile(string path);
    static void writeFile(string path, string contents);
public:
    static string currentPath;
    static void init();
    static void _new(string args[]);
    static void _search(string args[]);
    static void _run(string args[]);
    static void _clean(string args[]);
    static void _package(string args[]);
};


#endif