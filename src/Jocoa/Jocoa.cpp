#include "./Jocoa.hpp"
#include "./../Log/Logger.hpp"
#include "./../../lib/include/json.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace nlohmann;
using std::cout;
using std::cin;
using std::endl;

string Jocoa::currentPath = "";
JsonData Jocoa::jsonData;

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
    currentPath = std::filesystem::current_path().string();

    // Check if json file exists
    if (!std::filesystem::is_regular_file(currentPath + "/jocoa.json"))
    {
        Logger::warn("Invalid Project, no jocoa.json file found");
        return;
    }

    // Load json data from jocoa.json file
    std::fstream jsonFile(currentPath + "/jocoa.json");
    json json;
    jsonFile >> json;
    
    jsonData.name = json["name"];
    jsonData.type = json["type"];
    jsonData.package = json["package"];
    jsonData.sourceFiles = json["sourceFiles"];
    jsonData.dependencies = json["dependencies"];
    jsonData.natives = json["natives"];
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
        wchar_t userBuffer[UNLEN + 1];
        DWORD userLen = UNLEN + 1;
        GetUserNameW(userBuffer, &userLen);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        user = converter.to_bytes(userBuffer);
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
    type = typeStr[0];

    vector<string> packageTokens = split(packagePath, "/");

    // Create file and folders
    createDirectory(name);
    createDirectory(name + "/src");
    createDirectory(name + "/src/main");
    createDirectory(name + "/src/main/java");
    createDirectory(name + "/src/main/java/" + packageTokens[0]);
    createDirectory(name + "/src/main/java/" + packageTokens[0] + "/" + packageTokens[1]);
    createDirectory(name + "/src/main/java/" + packagePath);
    if (type == 'r') { createDirectory(name + "/src/main/java/" + packagePath + "/main"); }
    createDirectory(name + "/lib");
    createDirectory(name + "/lib/natives");
    createDirectory(name + "/res");
    createDirectory(name + "/bin");
    createFile(name + "/jocoa.json");
    writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"src/" + packagePath + "/main/Main.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t],\n\t\"natives\": \"lib/natives\"\n}");

    if (type == 'r')
    {
        createFile(name + "/src/main/java/" + packagePath + "/main/Main.java");
        writeFile(name + "/src/main/java/" + packagePath + "/main/Main.java", "package " + package + ".main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
    }
    else if (type == 'l')
    {
        // Create test stuff for library project type
        createDirectory(name + "/src/test");
        createDirectory(name + "/src/test/java");
        createDirectory(name + "/src/test/java/" + packageTokens[0]);
        createDirectory(name + "/src/test/java/" + packageTokens[0] + "/" + packageTokens[1]);
        createDirectory(name + "/src/test/java/" + packagePath);
        createDirectory(name + "/src/test/java/" + packagePath + "/main");
    }
}

void Jocoa::_search(string args[])
{
    // Check if current dir is a project
    if (!std::filesystem::is_regular_file(currentPath + "/jocoa.json"))
    {
        Logger::warn("Invalid Project, no jocoa.json file found");
        return;
    }

    // Get package as a path
    string packagePath = jsonData.package;
    for (int i = 0; i < packagePath.length(); i++) { if (packagePath[i] == '.') { packagePath[i] = '/'; } }

    // If runnable, just check the main folder
    if (jsonData.type[0] == 'r')
    {
        for (const auto& file : std::filesystem::recursive_directory_iterator(currentPath))
        {
            cout << file.path() << endl;
        }
    }
}

void Jocoa::_run(string args[])
{
    Jocoa::_search(NULL);

    if (!std::filesystem::is_regular_file(currentPath + "/jocoa.json"))
    {
        Logger::error("jocoa.json file does not exist");
        return;
    }

    if (strcmp(jsonData.type.c_str(), "runnable") == 0)
    {   
        for (auto &&i : jsonData.sourceFiles)
        {
            cout << i + ",";
        }
    }
}

void Jocoa::_clean(string args[])
{
    // Delete and recreate bin folder
    std::filesystem::remove_all(currentPath + "/" + jsonData.name + "/bin");
    createDirectory(jsonData.name + "bin");
}

void Jocoa::_package(string args[])
{
    // 
}
