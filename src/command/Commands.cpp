#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <filesystem>
#include "../json/JSONReader.hpp"
#include "Commands.hpp"
#include "CommandBuilder.hpp"

using std::cout;
using std::cerr;
using std::endl;

void Commands::createDirectory(string path)
{
    if (!std::filesystem::create_directory(path))
    {
        cerr << "Failed to create directory! \'" << path << "\'" << endl;
    }
    else
    {
        cout << "Created \'" + path + "\'" << endl;
    }
}

void Commands::createAndWriteFile(string path, string content)
{
    // Create file and write file with supplied contents
    std::ofstream file(path);
    file << content;
    file.close();
}

void Commands::run(char const *argv[])
{
    // Get JSON data
    JsonData jsonData = JSONReader::getJsonData();

    string command;

    if (sizeof(argv) / sizeof(argv[0]) > 2)
    {
        if (strcmp(argv[2], "jar") == 0)
        {
            // Build and run commands from JSON data for the .jar file
            command = CommandBuilder::buildJavaJarCommand(jsonData);
            system(command.c_str());
            return;
        }
    }

    // Build and run commands from JSON data for the .class files
    cout << "Compiling..." << endl;
    command = CommandBuilder::buildJavacCommand(jsonData);
    system(command.c_str());

    command = CommandBuilder::buildJavaCommand(jsonData);
    system(command.c_str());
    cout << "Done!" << endl;
}

void Commands::toJar(char const *argv[])
{
    // Get JSON data
    JsonData jsonData = JSONReader::getJsonData();

    string command;

    // Compile project to .jar file
    command = CommandBuilder::buildJavacCommand(jsonData);
    system(command.c_str());
    command = CommandBuilder::buildJarCommand(jsonData);
    system(command.c_str());
    command = CommandBuilder::buildJavaJarCommand(jsonData);
    system(command.c_str());
}

void Commands::_new(char const *argv[])
{
    // Get name from arguments
    string projectName = argv[2];
    // Get new project path
    string currentPath = std::filesystem::current_path().u8string() + OS_PATH_DELIMETER + projectName;

    // Create project directories
    createDirectory(currentPath);
    createDirectory(currentPath + OS_PATH_DELIMETER + "src");
    createDirectory(currentPath + OS_PATH_DELIMETER + "src" + OS_PATH_DELIMETER + "main");
    createDirectory(currentPath + OS_PATH_DELIMETER + "lib");
    createDirectory(currentPath + OS_PATH_DELIMETER + "lib" + OS_PATH_DELIMETER + "natives");
    createDirectory(currentPath + OS_PATH_DELIMETER + "bin");
    createDirectory(currentPath + OS_PATH_DELIMETER + "build");

    // Create JSON file and write basic setup
    createAndWriteFile(currentPath + OS_PATH_DELIMETER + "jocoa.json", 
        "{\n\t\"projectName\": \"" + projectName + "\",\n\t\"projectType\": \"Program\",\n\t\"sourceFiles\": \n\t[\n\t\t\"src/main/Main.java\"\n\t],\n\t\"dependencies\": [],\n\t\"natives\": \"lib/natives\",\n\t\"classpath\": \"bin\"\n}");
    // Create main Java file and write a basic program
    createAndWriteFile(currentPath + OS_PATH_DELIMETER + "src" + OS_PATH_DELIMETER + "main" + OS_PATH_DELIMETER + "Main.java", 
        "package main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
}

void Commands::help(char const *argv[])
{
    cout << "Usage:\n \t help \t\t\t\t Shows this command\n \t new <projectName> \t\t Creates new Jocoa Java project\n \t run \t\t\t\t Runs current Jocoa Java project\n \t to-jar \t\t\t Packages Jocoa Java project into a .jar file" << endl;
}

void Commands::search(char const *argv[])
{
    // Get JSON data
    JsonData jsonData = JSONReader::getJsonData();

    string currentPath = std::filesystem::current_path().u8string() + OS_PATH_DELIMETER;
    cout << currentPath << endl;
    std::filesystem::path currentPathFSP = currentPath;

    vector<string> newSourceFiles;
    string newJsonContent = "{\n\t\"projectName\": \"";
    string relativeDir;
    
    // Search source files for .java files and add them to the JSON file
    for (auto& dir : std::filesystem::recursive_directory_iterator(currentPathFSP))
    {
        if (dir.is_regular_file() && dir.path().extension() == ".java")
        {
            relativeDir = dir.path().c_str();
            relativeDir.erase(relativeDir.find(std::filesystem::current_path().u8string()), 1);
            newSourceFiles.push_back(relativeDir);
            cout << dir.path() << endl;
        }
    }

    cout << "Searched source files" << endl;

    // Truncate the JSON file and write the new contents
    std::ofstream file(currentPath + OS_PATH_DELIMETER + "jocoa.json", std::ios::trunc);

    // Check that the JSON file exists
    if (!file) { cout << "jocoa.json file does not exist" << endl; return; }

    file.clear();

    // Add new data to the JSON file
    newJsonContent += jsonData.projectName + "\",\n\t\"projectType\": \"" + jsonData.projectType + "\",\n\t\"sourceFiles\": \n\t[";

    for (int i = 0; i < newSourceFiles.size(); i++)
    {
        newJsonContent += "\n\t\t\"" + newSourceFiles[i] + "\"";
        
        if (i != jsonData.sourceFiles.size() - 1)
        {
            newJsonContent += ",";
        }
    }
    
    newJsonContent += "\n\t],\n\t\"dependencies\": \n\t[";

    for (auto &dependency : jsonData.dependencies)
    {
        newJsonContent += "\n\t\t\"" + dependency + "\",";
    }

    newJsonContent += "\n\t],\n\t\"natives\": \"" + jsonData.natives + "\",\n\t\"classpath\": \"" + jsonData.classpath + "\"\n}";

    file << newJsonContent;
    file.close();
    
}
