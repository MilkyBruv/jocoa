#include "./Jocoa.hpp"
#include "./../Log/Logger.hpp"
#include "./../../lib/include/json.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Jocoa.hpp"

using namespace nlohmann;
using std::cout;
using std::cin;
using std::endl;

string Jocoa::currentPath = "";

void Jocoa::createDirectory(string path)
{
    // Try create directory
    if (std::filesystem::create_directory(currentPath + "/" + path))
    {
        Logger::info("Created \t ./" + path);
    }
    else
    {
        Logger::error("Failed to create \t ./" + path);
    }
}

void Jocoa::createFile(string path)
{
    // Create file
    std::ofstream file(currentPath + "/" + path);
    file.close();
    Logger::info("Created \t ./" + path);
}

void Jocoa::writeFile(string path, string contents)
{
    // Create and write to file
    std::ofstream file(currentPath + "/" + path);
    file << contents;
    file.close();
    Logger::info("Wrote to \t ./" + path);
}

vector<string> Jocoa::split(string str, string delimiter)
{
    vector<string> tokens;
    string token;
    size_t pos = 0;

    // Loop through each appearance of delimiter and split the string into tokens
    while ((pos = str.find(delimiter)) != string::npos)
    {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    tokens.push_back(str);

    return tokens;
}

void Jocoa::init()
{
    // Get current path
    currentPath = std::filesystem::current_path();
}

void Jocoa::_help(string args[])
{

    cout << "\033[31m     _                       \n"
    "    | | ___   ___ ___   __ _ \n"
    " _  | |/ _ \\ / __/ _ \\ / _` |\n"
    "| |_| | (_) | (_| (_) | (_| |\n"
    " \\___/ \\___/ \\___\\___/ \\__,_|\n\n"
    "\033[39mCommands:\n"
    "\thelp - Displays this command\n"
    "\tnew - Creates new project\n"
    "\tsearch - Updates current jocoa.json file with all source files and dependency files in the current project\n"
    "\trun - Compiles current project to .class files and runs as a project" << endl;
}

void Jocoa::_new(string args[])
{
    string name, package, defaultPackage, packagePath, typeStr;
    char type;

    cout << "Enter options for new project (options marked with * are required)\n" << 
        endl;

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
    string user;
    #if defined(_WIN32) || defined(_WIN64)
        char userBuffer[UNLEN + 1];
        DWORD userLen = UNLEN + 1;
        GetUserName(userBuffer, &userLen);
        user = userBuffer;
    #elif defined(__linux__) || defined(_APPLE__) || defined(__unix__)
        char userBuffer[512];
        getlogin_r(userBuffer, 512);
        user = userBuffer;
    #endif
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
    cout << "Project type (r/l), leave blank for default (r): ";
    std::getline(cin, typeStr);
    cout << endl;
    if (typeStr.empty())
    {
        typeStr = "runnable";
    }
    if (typeStr[0] == 'r') { typeStr = "runnable"; }
    else if (typeStr[0] == 'l') { typeStr = "library"; }

    vector<string> packageTokens = split(packagePath, "/");

    // Create file and folders
    createDirectory(name);
    createDirectory(name + "/src");
    createDirectory(name + "/src/" + packageTokens[0]);
    createDirectory(name + "/src/" + packageTokens[0] + "/" + packageTokens[1]);
    createDirectory(name + "/src/" + packagePath);
    createDirectory(name + "/src/" + packagePath + "/main");
    createDirectory(name + "/lib");
    createDirectory(name + "/lib/natives");
    createDirectory(name + "/res");
    createDirectory(name + "/bin");
    createFile(name + "/jocoa.json");
    writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"src/" + packagePath + "/main/Main.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t],\n\t\"natives\": \"lib/natives\"\n}");
    createFile(name + "/src/" + packagePath + "/main/Main.java");
    writeFile(name + "/src/" + packagePath + "/main/Main.java", "package " + package + ".main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
}

void Jocoa::_search(string args[])
{
    // Check if current dir is a project
    if (!std::filesystem::is_regular_file(currentPath + "/jocoa.json"))
    {
        Logger::warn("Invalid Project, no jocoa.json file found");
        return;
    }

    // Check if main folder actually exists
    // if ()
}

void Jocoa::_run(string args[])
{
    Jocoa::_search(NULL);

    if (!std::filesystem::is_regular_file(currentPath + "/jocoa.json"))
    {
        Logger::error("jocoa.json file does not exist");
        return;
    }

    std::fstream jsonFile(currentPath + "/jocoa.json");
    json jsonData;
    jsonFile >> jsonData;
    
    Task task = {
        .name = jsonData["name"], 
        .type = jsonData["type"],
        .package = jsonData["package"],
        .sourceFiles = jsonData["sourceFiles"],
        .dependencies = jsonData["dependencies"],
        .natives = jsonData["natives"]
    };

    if (strcmp(task.type.c_str(), "runnable") == 0)
    {   
        for (auto &&i : task.sourceFiles)
        {
            cout << i + ",";
        }
    }
}

void Jocoa::_clean(string args[])
{
    // 
}

void Jocoa::_package(string args[])
{
    // 
}
