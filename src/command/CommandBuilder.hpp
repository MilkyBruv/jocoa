#ifndef COMMANDBUILDER_HPP
#define COMMANDBUILDER_HPP

#include <string>
#include "../json/JSONReader.hpp"

using std::string;

class CommandBuilder
{
public:
    // Build and return `javac` command from supplied JSON data.
    static string buildJavacCommand(JsonData jsonData);
    // Build and return `java` command from supplied JSON data.
    static string buildJavaCommand(JsonData jsonData);
    // Build and return `java` jar command from supplied JSON data.
    static string buildJavaJarCommand(JsonData jsonData);
    // Build and return `jar` command from supplied JSON data.
    static string buildJarCommand(JsonData jsonData);
};


#endif