#include "./CommandBuilder.hpp"
#include "CommandBuilder.hpp"

void CommandBuiler::initFATJar()
{
    FileManager::createDirectory("binf");
}

string CommandBuiler::buildClassRaw(vector<string> sourceFiles, vector<string> dependencies)
{
    string javac = "javac -d ./bin -cp .";

    // Add dependencies (.jar files)
    for (string& dependency : dependencies)
    {
        javac += CP_SEPARATOR + dependency;
    }

    // Add source files (.java)
    for (string& file : JsonManager::jsonData.sourceFiles)
    {
        javac += " " + file;
    }

    return javac;
}

string CommandBuiler::buildClassJson(JsonData data)
{
    // Pass json data into raw method
    return buildClassRaw(data.sourceFiles, data.dependencies);
}

string CommandBuiler::runClassRaw(vector<string> sourceFiles, vector<string> dependencies, string packagePath)
{
    string java = string("java -cp .") + CP_SEPARATOR + "./bin"; // Have to use string() else char* + char doesn't work

    // Add dependencies (.jar files)
    for (string& dependency : dependencies)
    {
        java += CP_SEPARATOR + dependency;
    }

    // Add natives path
    java += " -Djava.library.path=./lib/natives " + packagePath + "/main/Main";

    return java;
}

string CommandBuiler::runClassJson(JsonData data)
{
    // Pass json data into raw method
    return runClassRaw(data.sourceFiles, data.dependencies, data.packagePath);
}

string CommandBuiler::runJarRaw(string name, string packagePath)
{
    return "test";
}

string CommandBuiler::runJarJson(JsonData data)
{
    // Pass json data into raw method
    return runJarRaw(data.name, data.packagePath);
}

string CommandBuiler::buildRunnableJarRaw(string name, string package)
{
    // Build runnable jar with specified main class
    string jar = "jar cfe " + name + ".jar " + package + ".main.Main -C ./bin .";

    return jar;
}

string CommandBuiler::buildRunnableJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildRunnableJarRaw(data.name, data.package);
}

string CommandBuiler::buildLibraryJarRaw(string name)
{
    // Build library jar with no main class
    string jar = "jar cf " + name + ".jar ./bin .";

    return jar;
}

string CommandBuiler::buildLibraryJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildLibraryJarRaw(data.name);
}

string CommandBuiler::buildFATRunnableJarRaw(string name, string package, vector<string> dependencies)
{
    // Build runnable jar with specified main class
    string jar = "jar cfe " + name + ".jar " + package + ".main.Main -C ./bin .";

    return jar;
}

string CommandBuiler::buildFATRunnableJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildFATRunnableJarRaw(data.name, data.package, data.dependencies);
}

string CommandBuiler::buildFATLibraryJarRaw(string name, vector<string> dependencies)
{
    // Build library jar with no main class
    string jar = "jar cf " + name + ".jar ./bin .";

    return jar;
}

string CommandBuiler::buildFATLibraryJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildFATLibraryJarRaw(data.name, data.dependencies);
}
