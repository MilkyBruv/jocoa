#include "CommandBuilder.hpp"

/*
Java Commands:
 - javac -d <classfiles dir> -cp .;1.jar;2,jar dir1/*.java dir2/*.java
 - java -cp .;<classfiles>;1.jar;2.jar -Djava.library.path=<dll dir> main/Main
*/

// Set classpath delimeter for OS
#if defined(_WIN32) || defined(__WINDOWS__)
    #define OS_DELIMITER ";"
#elif defined(__unix__) || defined(__linux__)
    #define OS_DELIMETER ":"
#endif

string CommandBuilder::buildJavacCommand(JsonData jsonData)
{
    // Begin command creation
    string finalCommand = "javac -d " + jsonData.classpath + " -cp .";

    // Add dependencies and source files to command
    for (const auto &dependency : jsonData.dependencies) { finalCommand += OS_DELIMETER + dependency; }
    for (const auto &sourceFile : jsonData.sourceFiles) { finalCommand += " " + sourceFile; }

    // Return command
    return finalCommand;
}

string CommandBuilder::buildJavaCommand(JsonData jsonData)
{
    // Begin command creation
    string finalCommand = "java -cp .";
    finalCommand += OS_DELIMETER + jsonData.classpath;

    // Add dependencies to command
    for (const auto &dependency : jsonData.dependencies) { finalCommand += OS_DELIMETER + dependency; }
    
    // Add natives directory to command
    finalCommand += " -Djava.library.path=" + jsonData.natives + " main/Main";

    // Return command
    return finalCommand;
}

string CommandBuilder::buildJavaJarCommand(JsonData jsonData)
{
    // Create command
    string finalCommand = "java -jar build/" + jsonData.projectName + ".jar";

    // Return command
    return finalCommand;
}

string CommandBuilder::buildJarCommand(JsonData jsonData)
{
    // Create command
    string finalCommand = "jar --create --file build/" + jsonData.projectName + ".jar --main-class main.Main -C " + jsonData.classpath + "/ .";

    // Return command
    return finalCommand;
}
