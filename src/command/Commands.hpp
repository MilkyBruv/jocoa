#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>

using std::string;

#if defined(_WIN32) || defined(__WINDOWS__)
    #define OS_PATH_DELIMETER "\\"
#elif defined(__unix__) || defined(__linux__)
    #define OS_PATH_DELIMETER "/"
#endif

/*
Commands:
 - run jar
 - to-jar
 - new (create new project)
 - help (shows list of commands)
*/

/*
Java Commands:
 - javac -d <classfiles dir> -cp .;1.jar;2,jar dir1/*.java dir2/*.java
 - java -cp .;<classfiles>;1.jar;2.jar -Djava.library.path=<dll dir> main/Main
*/

class Commands
{
private:
    static void createDirectory(string path);
    static void createAndWriteFile(string path, string content);
    static bool getVerboseState(char const *argv[]);
public:
    static void run(char const *argv[]);
    static void toJar(char const *argv[]);
    static void _new(char const *argv[]);
    static void help(char const *argv[]);
    static void search(char const *argv[]);
};


#endif