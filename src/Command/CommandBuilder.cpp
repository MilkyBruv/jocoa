#include "./CommandBuilder.hpp"

string CommandBuiler::javacRaw(vector<string> sourceFiles, vector<string> dependencies)
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

string CommandBuiler::javacJson(JsonData data)
{
    // Pass json data into raw method
    return javacRaw(data.sourceFiles, data.dependencies);
}

string CommandBuiler::javaRaw(vector<string> sourceFiles, vector<string> dependencies, string packagePath)
{
    string java = string("java -cp .") + CP_SEPARATOR + "./bin"; // Have to use string() else char* + char doesn't work

    // Add dependencies (.jar files)
    for (string& dependency : dependencies)
    {
        java += CP_SEPARATOR + dependency;
    }

    // Add natives path
    java += " -Djava.library.path=./lib/natives " + packagePath + "/main/Main";
}

string CommandBuiler::javaJson(JsonData data)
{
    // Pass json data into raw method
    return javaRaw(data.sourceFiles, data.dependencies, data.packagePath);
}
