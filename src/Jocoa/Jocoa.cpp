#include "./Jocoa.hpp"
#include "./../Log/Logger.hpp"
#include "./../File/FileManager.hpp"
#include "./../Json/JsonManager.hpp"
#include <iostream>
#include <filesystem>
#include "Jocoa.hpp"


namespace fs = std::filesystem;
using std::cout;
using std::cin;
using std::endl;

string Jocoa::version = "v0.1.0";

void Jocoa::init(string args[])
{
    // Check if json file exists
    if (!FileManager::fileExists("jocoa.json"))
    {
        Logger::warn("Invalid Project, no jocoa.json file found");
        return;
    }

    JsonManager::loadJsonData();
}

void Jocoa::_help(string args[])
{
    cout << 
    "\033[31m"
    "     _\n"
    "    | | ___   ___ ___   __ _ \t\033[36m" + version + "\033[31m\n"
    " _  | |/ _ \\ / __/ _ \\ / _` |\n"
    "| |_| | (_) | (_| (_) | (_| |\n"
    " \\___/ \\___/ \\___\\___/ \\__,_|\t\033[36mgithub.com/MilkyBruv 2025\n\n"
    "\033[39mCommands:\n"
    "\thelp - Displays this command\n"
    "\tnew - Creates new project\n"
    "\trun \033[36mnosearch\033[39m - Compiles current project to .class files and runs as a project\n"
    "\t\t\033[36mnosearch\033[39m - Runs the current project without searching for new libraries and files and adding them to the jocoa.json file\n"
    "\tpackage \033[36mrun\033[39m - Compiles current project to .class files and packages it to a single .jar\n"
    "\t\t\033[36mrun\033[39m - Runs the .jar file after packing it\n"
    "\tsearch - Updates current jocoa.json file with all source files and dependency files in the current project\n"
    "\tclean - Cleans current project of compilation files" << endl;
}

void Jocoa::_new(string args[])
{
    string name, package, defaultPackage, packagePath, typeStr;

    cout << "Enter options for new project (options marked with * are required)\n" << endl;

    // Project name
    cout << "*Project name: ";
    std::getline(cin, name);
    cout << endl;

    if (name.empty())
    {
        Logger::error("Project name must be specified");
        return;
    }

    // Package

    // Get system username
    string user = FileManager::getSystemUser();
    defaultPackage = "net." + user + "." + name;

    cout << "Package, leave blank for default (" + defaultPackage + "): ";
    std::getline(cin, package);
    cout << endl;
    if (package.empty())
    {
        package = defaultPackage;
    }

    packagePath = package;
    for (int i = 0; i < packagePath.length(); i++)
    {
        if (packagePath[i] == '.') { packagePath[i] = '/'; }
    }

    // Type
    cout << "Project type (runnable,r/library,l), leave blank for default (runnable, r): ";
    std::getline(cin, typeStr);
    cout << endl;
    if (typeStr.empty())
    {
        typeStr = "runnable";
    }
    if (typeStr[0] == 'r') { typeStr = "runnable"; }
    else if (typeStr[0] == 'l') { typeStr = "library"; }
    else { typeStr = "runnable"; }

    // Create file and folders
    FileManager::createDirectory(name + "/src/" + packagePath);
    if (typeStr[0] == 'r') { FileManager::createDirectory(name + "/src/" + packagePath + "/main"); }
    FileManager::createDirectory(name + "/lib/natives");
    FileManager::createDirectory(name + "/res");
    FileManager::createDirectory(name + "/bin");
    FileManager::createFile(name + "/jocoa.json");

    if (typeStr[0] == 'r')
    {
        FileManager::writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"./src/" + packagePath + "/main/Main.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t],\n\t\"natives\": \"lib/natives\"\n}");
        FileManager::createFile(name + "/src/" + packagePath + "/main/Main.java");
        FileManager::writeFile(name + "/src/" + packagePath + "/main/Main.java", "package " + package + ".main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
    }
    else if (typeStr[0] == 'l')
    {
        // Create and package main library
        FileManager::writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"./src/" + packagePath + "/library/Library.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t],\n\t\"natives\": \"lib/natives\"\n}");
        FileManager::createDirectory(name + "/src/" + packagePath + "/library");
        FileManager::createFile(name + "/src/" + packagePath + "/library/Library.java");
        FileManager::writeFile(name + "/src/" + packagePath + "/library/Library.java", "package " + package + ".library;\n\npublic class Library {\n\n\tpublic static void test() {\n\n\t\tSystem.out.println(\"Hello World from Library!\");\n\n\t}\n\n}");

        // Create test stuff for library project type
        FileManager::createDirectory(name + "/test/" + packagePath + "Test/main");
        FileManager::createFile(name + "/test/" + packagePath + "Test/main/Main.java");
        FileManager::writeFile(name + "/test/" + packagePath + "Test/main/Main.java", "package " + package + ".main;\n\nimport " + package + ".library.Library;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");

        // Package in new project mode
        args[0] = "internal_new";
        JsonManager::loadJsonData();
        _package(args);
    }
}

void Jocoa::_search(string args[])
{
    // Check if current dir is a project
    if (!FileManager::fileExists("jocoa.json"))
    {
        Logger::warn("Invalid Project, no jocoa.json file found");
        return;
    }

    // If runnable, just check the main folder
    string currentFile;
    string pathToCheck;

    string newJson = "{\n\t\"name\": \"" + jsonData.name + "\",\n\t\"type\": \"" + jsonData.type + "\",\n\t\"package\": \"" + jsonData.package + "\",\n\t\"sourceFiles\": [";

    // Clear current source files and dependencies
    jsonData.sourceFiles.clear();
    jsonData.dependencies.clear();

    // Search for source files and libraries
    searchForFiles("src", ".java", jsonData.sourceFiles);
    searchForFiles("lib", ".jar", jsonData.dependencies);

    if (jsonData.sourceFiles.size() != 0)
    {
        for (size_t i = 0; i < jsonData.sourceFiles.size(); i++)
        {
            newJson += "\n\t\t\"" + jsonData.sourceFiles[i] + "\"";

            // If not at the end then add ",", else move onto dependencies
            if (i != jsonData.sourceFiles.size() - 1) { newJson += ","; }
        }
    }
    else { newJson += "\n"; } // Add new line between [] if no sourceFiles for cleaner json

    newJson += "\n\t],\n\t\"dependencies\": [";
    
    if (jsonData.dependencies.size() != 0)
    {
        for (size_t i = 0; i < jsonData.dependencies.size(); i++)
        {
            newJson += "\n\t\t\"" + jsonData.dependencies[i] + "\"";

            // If not at the end then add ",", else add rest of json data
            if (i != jsonData.dependencies.size() - 1) { newJson += ","; }
        }
    }
    else { newJson += "\n"; } // Add new line between [] if no dependencies for cleaner json
    
    newJson += "\n\t],\n\t\"natives\": \"" + jsonData.natives + "\"\n}";

    // Write new json data to json file
    FileManager::writeFile("jocoa.json", newJson);
}

void Jocoa::_run(string args[])
{
    if (FileManager::fileExists("jocoa.json"))
    {
        Logger::error("jocoa.json file does not exist");
        return;
    }

    if (strcmp(args[2].c_str(), "no-search") != 0) { Jocoa::_search(args); } // Check if should search before running

    string javac = "javac -d ./bin -cp .";
    string java = string("java -cp .") + CP_SEPARATOR + "./bin"; // Have to use string() else char* + char doesn't work

    // If runnable then just compile to class then run
    if (JsonManager::jsonData.type[0] == 'r')
    {   
        // Add dependencies (.jar files)
        for (string& dependency : JsonManager::jsonData.dependencies)
        {
            javac += CP_SEPARATOR + dependency;
            java += CP_SEPARATOR + dependency;
        }

        // Add natives path
        java += " -Djava.library.path=./lib/natives " + JsonManager::jsonData.packagePath + "/main/Main";

        // Add source files (.java files)
        for (string& file : JsonManager::jsonData.sourceFiles)
        {
            javac += " " + file;
        }
    }
    else if (JsonManager::jsonData.type[0] == 'l') // If library then package src/main then run src/test
    {
        _package(args); // Package to .jar and use as a library for src/test source files

        FileManager::searchForFiles("src", ".java", JsonManager::jsonData.sourceFiles);
        FileManager::searchForFiles("lib", ".jar", JsonManager::jsonData.dependencies);

        for (const string& dependency : JsonManager::jsonData.dependencies)
        {
            javac += CP_SEPARATOR + dependency;
            java += CP_SEPARATOR + dependency;
        }

        for (const string& file : JsonManager::jsonData.sourceFiles)
        {
            javac += " " + file;
        }
    }

    // Run and print commands
    cout << javac << endl;
    system(javac.c_str());
    cout << java << endl;
    system(java.c_str());
}

void Jocoa::_clean(string args[])
{
    // Delete and recreate bin folder
    FileManager::clearDirectory("bin");
}

void Jocoa::_package(string args[])
{
    string jar = "jar cf";
    string java;

    // Check if not in new project mode
    if (args[0][0] != 'n') { _search(args); }

    // If runnable compile to jar with main method
    if (JsonManager::jsonData.type[0] == 'r')
    {
        jar += "e " + JsonManager::jsonData.name + ".jar " + JsonManager::jsonData.package + ".main.Main -C ./bin .";

        // Run command
        cout << jar << endl;
        system(jar.c_str());

        // Run jar file if specified to
        if (strcmp(args[2].c_str(), "run") == 0)
        {
            java = "java -jar ./" + JsonManager::jsonData.name + ".jar";

            // Run command
            cout << java << endl;
            system(java.c_str());
        }
    }
    else if (JsonManager::jsonData.type[0] == 'l') // If library then compile to jar without main method
    {
        // Compile to ./x.jar and ./lib/x.jar
        jar += " " + JsonManager::jsonData.name + ".jar -C ./bin .";

        // Run commands
        cout << jar << endl;
        system(jar.c_str());

        // Run jar file if specified to
        if (strcmp(args[2].c_str(), "run") == 0)
        {
            // Run test files with packaged .jar as a library
            _run(args);
        }
    }
}
