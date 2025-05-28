#include "./CommandBuilder.hpp"

void CommandBuiler::initFATJar()
{
    FileManager::createDirectory("binf");
}

void CommandBuiler::unpackDependencies(vector<string> dependencies)
{
    initFATJar();

    string jar;

    // Loop through each dependency in ./lib and unpack into .class files in ./binf
    for (const string& dependency : dependencies)
    {
        jar = "cd binf && jar xf ../" + dependency + " && cd ..";
        system(jar.c_str());
    }

    // Copy ./bin into ./binf
    system("cp -r ./bin/* ./binf");
}

string CommandBuiler::buildClassRaw(vector<string> sourceFiles, vector<string> dependencies)
{
    string javac = "javac -d ./bin -cp \".";

    // Add dependencies (.jar files)
    for (string& dependency : dependencies)
    {
        javac += CP_SEPARATOR + dependency;
    }

    javac += "\"";

    // Add source files (.java)
    for (string& file : sourceFiles)
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
    string java = string("java -cp \".") + CP_SEPARATOR + "./bin"; // Have to use string() else char* + char doesn't work

    // Add dependencies (.jar files)
    for (string& dependency : dependencies)
    {
        java += CP_SEPARATOR + dependency;
    }

    java += "\"";

    // Add natives path
    java += " -Djava.library.path=./lib/natives " + packagePath + "/main/Main";

    return java;
}

string CommandBuiler::runClassJson(JsonData data)
{
    // Pass json data into raw method
    return runClassRaw(data.sourceFiles, data.dependencies, data.packagePath);
}

string CommandBuiler::buildRunJarRaw(string name, string packagePath)
{
    return "java -jar " + name + ".jar " + packagePath + "/main/Main";
}

string CommandBuiler::buildRunJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildRunJarRaw(data.name, data.package);
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
    string jar = "jar cf " + name + ".jar -C ./bin .";

    return jar;
}

string CommandBuiler::buildLibraryJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildLibraryJarRaw(data.name);
}

string CommandBuiler::buildFATRunnableJarRaw(string name, string package, vector<string> dependencies)
{
    // Unpack dependencies
    unpackDependencies(dependencies);

    // Build runnable jar with specified main class
    string jar = "jar cfe " + name + ".jar " + package + ".main.Main -C ./binf .";

    return jar;
}

string CommandBuiler::buildFATRunnableJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildFATRunnableJarRaw(data.name, data.package, data.dependencies);
}

string CommandBuiler::buildFATLibraryJarRaw(string name, vector<string> dependencies)
{
    // Unpack dependencies
    unpackDependencies(dependencies);

    // Build library jar with no main class
    string jar = "jar cf " + name + ".jar ./bin .";

    return jar;
}

string CommandBuiler::buildFATLibraryJarJson(JsonData data)
{
    // Pass json data into raw method
    return buildFATLibraryJarRaw(data.name, data.dependencies);
}
