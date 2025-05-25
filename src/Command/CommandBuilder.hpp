#ifndef COMMAND_BUILDER_HPP
#define COMMAND_BUILDER_HPP

#include "./../Json/JsonManager.hpp"

class CommandBuiler
{
private:
    static void initFATJar();
    static void unpackDependencies(vector<string> dependencies);
public:
    static string buildClassRaw(vector<string> sourceFiles, vector<string> dependencies);
    static string buildClassJson(JsonData data);

    static string runClassRaw(vector<string> sourceFiles, vector<string> dependencies, string packagePath);
    static string runClassJson(JsonData data);

    static string buildRunJarRaw(string name, string packagePath);
    static string buildRunJarJson(JsonData data);

    static string buildRunnableJarRaw(string name, string package);
    static string buildRunnableJarJson(JsonData data);

    static string buildLibraryJarRaw(string name);
    static string buildLibraryJarJson(JsonData data);

    static string buildFATRunnableJarRaw(string name, string package, vector<string> dependencies);
    static string buildFATRunnableJarJson(JsonData data);

    static string buildFATLibraryJarRaw(string name, vector<string> dependencies);
    static string buildFATLibraryJarJson(JsonData data);
};

#endif