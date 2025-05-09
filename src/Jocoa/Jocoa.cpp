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
    std::filesystem::resize_file(currentPath + "/" + path, 0);
    file.close();
    Logger::info("Created \t ./" + path);
}

void Jocoa::writeFile(string path, string contents)
{
    // Create and write to file
    std::ofstream file(currentPath + "/" + path);
    std::filesystem::resize_file(currentPath + "/" + path, 0);
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

void Jocoa::standardisePath(string& path)
{
    string delimiters[] = {"\\\\", "\\"};

    // Loop through each delimiter, and replace all occurences with standard "/"
    for (const auto& delimiter : delimiters)
    {
        size_t i = 0;
        while ((i = path.find(delimiter, i)) != string::npos)
        {
            path.replace(i, delimiter.length(), "/");
            i++;
        }
    }
}

void Jocoa::localisePath(string &path)
{
    // Replace currentPath with "."
    path.replace(0, currentPath.length(), ".");
}

void Jocoa::simplifyPath(string &path)
{
    // Standardise and localise path
    standardisePath(path);
    localisePath(path);
}

void Jocoa::init(string args[])
{
    // Get current path
    currentPath = std::filesystem::current_path().string();
    standardisePath(currentPath);
    
    if (strcmp(args[1].c_str(), "repair") != 0)
    {
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
}

void Jocoa::_help(string args[])
{
    cout << 
    "\033[31m"
    "     _\n"
    "    | | ___   ___ ___   __ _ \t\033[36mv0.1.0\033[31m\n"
    " _  | |/ _ \\ / __/ _ \\ / _` |\n"
    "| |_| | (_) | (_| (_) | (_| |\n"
    " \\___/ \\___/ \\___\\___/ \\__,_|\t\033[36mgithub.com/MilkyBruv 2025\n\n"
    "\033[39mCommands:\n"
    "\thelp - Displays this command\n"
    "\tnew - Creates new project\n"
    "\trun - Compiles current project to .class files and runs as a project\n"
    "\tpackage \033[36m<run>\033[39m - Compiles current project to .class files and packages it to a single .jar\n"
    "\t\t\033[36mrun\033[39m - Runs the .jar file after packing it\n"
    "\tsearch - Updates current jocoa.json file with all source files and dependency files in the current project\n"
    "\tclean - Cleans current project of compilation files\n"
    "\trepair - Confirms project information to repair the jocoa.json file if it is broken" << endl;
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
    cout << "Project type (runnable, r/library, l), leave blank for default (runnable, r): ";
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
    createDirectory(name + "/src/main");
    createDirectory(name + "/src/main/java");
    createDirectory(name + "/src/main/java/" + packageTokens[0]);
    createDirectory(name + "/src/main/java/" + packageTokens[0] + "/" + packageTokens[1]);
    createDirectory(name + "/src/main/java/" + packagePath);
    if (typeStr[0] == 'r') { createDirectory(name + "/src/main/java/" + packagePath + "/main"); }
    createDirectory(name + "/lib");
    createDirectory(name + "/lib/natives");
    createDirectory(name + "/res");
    createDirectory(name + "/bin");
    createFile(name + "/jocoa.json");
    writeFile(name + "/jocoa.json", "{\n\t\"name\": \"" + name + "\",\n\t\"type\": \"" + typeStr + "\",\n\t\"package\": \"" + package + "\",\n\t\"sourceFiles\": [\n\t\t\"src/" + packagePath + "/main/Main.java\"\n\t],\n\t\"dependencies\": [\n\t\t\n\t],\n\t\"natives\": \"lib/natives\"\n}");

    if (typeStr[0] == 'r')
    {
        createFile(name + "/src/main/java/" + packagePath + "/main/Main.java");
        writeFile(name + "/src/main/java/" + packagePath + "/main/Main.java", "package " + package + ".main;\n\npublic class Main {\n\n\tpublic static void main(String[] args) {\n\n\t\tSystem.out.println(\"Hello World!\");\n\n\t}\n\n}");
    }
    else if (typeStr[0] == 'l')
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
    string currentFile;
    string pathToCheck;

    string newJson = "{\n\t\"name\": \"" + jsonData.name + "\",\n\t\"type\": \"" + jsonData.type + "\",\n\t\"package\": \"" + jsonData.package + "\",\n\t\"sourceFiles\": [";

    // Clear current source files and dependencies
    jsonData.sourceFiles.clear();
    jsonData.dependencies.clear();

    // Find all .java and .jar files and add them to sourceFiles and dependencies
    // Only check "src/main" to avoid searching "src/test"
    for (const auto& file : std::filesystem::recursive_directory_iterator(currentPath + "/src/main"))
    {   
        if (file.path().extension() == ".java")
        {
            currentFile = file.path().string(); // Add "src/main/" back to path
            simplifyPath(currentFile);
            jsonData.sourceFiles.push_back(currentFile);
            cout << currentFile << endl;
        }
        else if (file.path().extension() == ".jar")
        {
            currentFile = file.path().string();
            simplifyPath(currentFile);
            jsonData.dependencies.push_back(currentFile);
            cout << currentFile << endl;
        }
    }

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
    writeFile("jocoa.json", newJson);
}

void Jocoa::_run(string args[])
{
    Jocoa::_search(args);

    if (!std::filesystem::is_regular_file(currentPath + "/jocoa.json"))
    {
        Logger::error("jocoa.json file does not exist");
        return;
    }

    string javac = "javac -d ./bin -cp .";
    string java = string("java -cp .") + CP_SEPARATOR + "./bin"; // Have to use string() else char* + char doesn't work

    // If runnable then just compile to class then run
    if (jsonData.type[0] == 'r')
    {   
        // Add dependencies (.jar files)
        for (string& dependency : jsonData.dependencies)
        {
            javac += CP_SEPARATOR + dependency;
            java += CP_SEPARATOR + dependency;
        }

        // Create package path
        string packagePath = jsonData.package;
        for (int i = 0; i < packagePath.length(); i++)
        {
            if (packagePath[i] == '.') { packagePath[i] = '/'; }
        }

        // Add natives path
        java += " -Djava.library.path=./lib/natives " + packagePath + "/main/Main";

        // Add source files (.java files)
        for (string& file : jsonData.sourceFiles)
        {
            javac += " " + file;
        }
    }
    else if (jsonData.type[0] == 'l') // If library then package src/main then run src/test
    {
        for (string& dependency : jsonData.dependencies)
        {
            javac += CP_SEPARATOR + dependency;
        }

        for (string& file : jsonData.sourceFiles)
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
    std::filesystem::remove_all(currentPath + "/bin");
    createDirectory("bin");
}

void Jocoa::_package(string args[])
{
    string jar = "jar cf";
    string jarLib, java;

    // If runnable compile to jar with main method
    if (jsonData.type[0] == 'r')
    {
        jar += "e " + jsonData.name + ".jar " + jsonData.package + ".main.Main -C ./bin .";

        // Run command
        cout << jar << endl;
        system(jar.c_str());

        // Run jar file if specified to
        if (strcmp(args[2].c_str(), "run") == 0)
        {
            java = "java -jar ./" + jsonData.name + ".jar";

            // Run command
            cout << java << endl;
            system(java.c_str());
        }
    }
    else if (jsonData.type[0] == 'l') // If library compile to jar without main method
    {
        // Compile to ./x.jar and ./lib/x.jar
        jar += jsonData.name + ".jar -C ./bin ";
        jarLib = jar + "./lib";
        jar += '.';

        // Run commands
        cout << jar << endl;
        system(jar.c_str());
        cout << jarLib << endl;
        system(jarLib.c_str());
    }
}

void Jocoa::_repair(string args[])
{
    string typeStr, name, package, packagePath, currentFile;
    string newJson = "{\n\t\"name\": \"" + jsonData.name + "\",\n\t\"type\": \"" + jsonData.type + "\",\n\t\"package\": \"" + jsonData.package + "\",\n\t\"sourceFiles\": [";

    // Get project name from current path (current/last folder)
    name = currentPath.substr(currentPath.find_last_of("/"), currentPath.length());

    // Confirm project package
    cout << "Package: ";
    std::getline(cin, package);
    cout << endl;
    if (package.empty())
    {
        cout << "Please supply a package" << endl;
        return;
    }

    // Create package path
    packagePath = package;
    for (int i = 0; i < packagePath.length(); i++)
    {
        if (packagePath[i] == '.') { packagePath[i] = '/'; }
    }

    // Confirm project type
    cout << "Confirm project type (runnable, r/library, l): ";
    std::getline(cin, typeStr);
    cout << endl;
    if (typeStr.empty())
    {
        cout << "Please supply a project type" << endl;
        return;
    }
    if (typeStr[0] == 'r') { typeStr = "runnable"; }
    else if (typeStr[0] == 'l') { typeStr = "library"; }

    // Confirm all .java and .jar files and add them to sourceFiles and dependencies
    // Only check "src/main" to avoid searching "src/test"
    for (const auto& file : std::filesystem::recursive_directory_iterator(currentPath + "/src/main"))
    {   
        if (file.path().extension() == ".java")
        {
            currentFile = file.path().string(); // Add "src/main/" back to path
            simplifyPath(currentFile);
            jsonData.sourceFiles.push_back(currentFile);
            cout << currentFile << endl;
        }
        else if (file.path().extension() == ".jar")
        {
            currentFile = file.path().string();
            simplifyPath(currentFile);
            jsonData.dependencies.push_back(currentFile);
            cout << currentFile << endl;
        }
    }

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
    
    newJson += "\n\t],\n\t\"natives\": \"lib/natives\"\n}";

    // Rewrite jocoa.json wit new json data
    writeFile("jocoa.json", newJson);
}
