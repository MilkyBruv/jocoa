#ifndef COMMAND_BUILDER_HPP
#define COMMAND_BUILDER_HPP

#include "./../Json/JsonManager.hpp"

class CommandBuiler
{
public:
    static string javacRaw(vector<string> sourceFiles, vector<string> dependencies);
    static string javacJson(JsonData data);

    static string javaRaw(vector<string> sourceFiles, vector<string> dependencies, string packagePath);
    static string javaJson(JsonData data);

    static string runJarRaw(string name, string packagePath);
    static string runJarJson(JsonData data);
    
    static string buildJarRaw(string name, string packagePath);
    static string buildJarJson(JsonData data);
};

#endif